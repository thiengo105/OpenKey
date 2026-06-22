/*
 * OpenKey for Fcitx5 - input method engine implementation.
 *
 * The OpenKey engine works on a "delete N characters, then emit M characters"
 * model (vKeyHookState). On macOS/Windows that is realised by synthesising
 * backspaces and Unicode key events. On Linux/Wayland the only reliable way is
 * to keep the word being typed in the Fcitx5 *preedit* buffer, redraw it on
 * every keystroke, and commit it at a word boundary - exactly what
 * fcitx5-unikey does.
 */
#include "openkeyengine.h"

#include <cstdint>
#include <string>

#include <fcitx-utils/capabilityflags.h>
#include <fcitx-utils/key.h>
#include <fcitx-utils/keysym.h>
#include <fcitx-utils/textformatflags.h>
#include <fcitx-utils/utf8.h>
#include <fcitx/inputcontext.h>
#include <fcitx/inputcontextmanager.h>
#include <fcitx/inputpanel.h>
#include <fcitx/text.h>
#include <fcitx/userinterface.h>

// OpenKey's platform independent engine. Included at global scope and built
// with -DLINUX so DataType.h selects platforms/linux.h (XKB key codes).
#include "Engine.h"

// ---------------------------------------------------------------------------
// OpenKey engine configuration globals.
// These are declared `extern` in Engine.h and must be defined by the host
// application. The configurable ones are overwritten by populateConfig().
// ---------------------------------------------------------------------------
int vLanguage = 1; // 1 = Vietnamese. The engine only sees keys while active.
int vInputType = 0;
int vFreeMark = 0;
int vCodeTable = 0; // 0 = Unicode (the only output charset for the MVP).
int vSwitchKeyStatus = 0;
int vCheckSpelling = 1;
int vUseModernOrthography = 1;
int vQuickTelex = 0;
int vRestoreIfWrongSpelling = 1;
int vFixRecommendBrowser = 0;
int vUseMacro = 0;
int vUseMacroInEnglishMode = 0;
int vAutoCapsMacro = 0;
int vUseSmartSwitchKey = 0; // Fcitx5 provides per-program input state itself.
int vUpperCaseFirstChar = 0;
int vTempOffSpelling = 0;
int vAllowConsonantZFWJ = 0;
int vQuickStartConsonant = 0;
int vQuickEndConsonant = 0;
int vRememberCode = 0;
int vOtherLanguage = 1;
int vTempOffOpenKey = 0;

namespace {

// The engine keeps a single global result block; vKeyInit() returns a pointer
// to it. Only the focused input context types at a time, so sharing it is safe
// as long as we reset the engine on every focus change.
vKeyHookState *gHook = nullptr;

// Remove the last `n` *characters* (not bytes) from a UTF-8 string.
void eraseLastChars(std::string &str, int n) {
    int k = n;
    int i;
    for (i = static_cast<int>(str.length()) - 1; i >= 0 && k > 0; i--) {
        auto c = static_cast<unsigned char>(str[i]);
        // Count down once per UTF-8 lead byte (ASCII or >= 0xC0).
        if (c < 0x80 || c >= 0xC0) {
            k--;
        }
    }
    str.erase(i + 1);
}

} // namespace

namespace fcitx {

class OpenKeyState final : public InputContextProperty {
public:
    OpenKeyState(OpenKeyEngine *engine, InputContext *ic)
        : engine_(engine), ic_(ic) {}

    void keyEvent(KeyEvent &keyEvent);

    // Commit the pending word (if any) and reset both buffers.
    void commit() {
        if (!preedit_.empty()) {
            ic_->commitString(preedit_);
            preedit_.clear();
        }
        startNewSession();
        updatePreedit();
    }

    // Discard the pending word.
    void reset() {
        preedit_.clear();
        startNewSession();
        updatePreedit();
    }

private:
    void handleIgnoredKey() { commit(); }
    void syncState(KeySym sym, uint16_t keycode, int caps);
    void appendEngineChar(uint32_t value);
    void updatePreedit();

    OpenKeyEngine *engine_;
    InputContext *ic_;
    std::string preedit_;
};

// Decode one entry of the engine's output buffer into the preedit string.
// Only the Unicode (vCodeTable == 0) decoding is needed; Vietnamese characters
// are all in the BMP, so each entry maps to a single code point.
void OpenKeyState::appendEngineChar(uint32_t value) {
    uint32_t cp;
    if (value & PURE_CHARACTER_MASK) {
        cp = value & CHAR_MASK; // already a literal character
    } else if (!(value & CHAR_CODE_MASK)) {
        cp = keyCodeToCharacter(value); // a raw key code (+ caps mask)
    } else {
        cp = value & CHAR_MASK; // an encoded character (Unicode table)
    }
    if (cp) {
        preedit_ += utf8::UCS4ToUTF8(cp);
    }
}

// Apply the engine result (gHook) to the preedit buffer.
void OpenKeyState::syncState(KeySym sym, uint16_t keycode, int caps) {
    const Byte code = gHook->code;
    if (code == vWillProcess || code == vRestore ||
        code == vRestoreAndStartNewSession || code == vReplaceMaro) {
        eraseLastChars(preedit_, gHook->backspaceCount);
        if (code == vReplaceMaro) {
            for (uint32_t value : gHook->macroData) {
                appendEngineChar(value);
            }
        } else {
            // charData is filled in reverse order; read it back to front.
            for (int k = static_cast<int>(gHook->newCharCount) - 1; k >= 0; k--) {
                appendEngineChar(gHook->charData[k]);
            }
        }
        if (code == vRestore || code == vRestoreAndStartNewSession) {
            uint16_t ch = keyCodeToCharacter(keycode | (caps ? CAPS_MASK : 0));
            if (ch) {
                preedit_ += utf8::UCS4ToUTF8(ch);
            }
        }
    } else {
        // vDoNothing: the engine did not transform the key, so show it as-is.
        if (sym >= FcitxKey_space && sym <= FcitxKey_asciitilde) {
            preedit_ += utf8::UCS4ToUTF8(static_cast<uint32_t>(sym));
        }
    }
}

void OpenKeyState::updatePreedit() {
    auto &inputPanel = ic_->inputPanel();
    inputPanel.reset();
    if (!preedit_.empty()) {
        const bool useClientPreedit =
            ic_->capabilityFlags().test(CapabilityFlag::Preedit);
        Text text(preedit_,
                  (useClientPreedit && *engine_->config().displayUnderline)
                      ? TextFormatFlag::Underline
                      : TextFormatFlag::NoFlag);
        text.setCursor(preedit_.size());
        if (useClientPreedit) {
            inputPanel.setClientPreedit(text);
        } else {
            inputPanel.setPreedit(text);
        }
    }
    ic_->updatePreedit();
    ic_->updateUserInterface(UserInterfaceComponent::InputPanel);
}

void OpenKeyState::keyEvent(KeyEvent &keyEvent) {
    if (keyEvent.isRelease()) {
        return;
    }

    const KeySym sym = keyEvent.rawKey().sym();
    const KeyStates states = keyEvent.rawKey().states();

    // Lone modifier / lock keys: ignore, do not break the current word.
    if (sym >= FcitxKey_Shift_L && sym <= FcitxKey_Hyper_R) {
        return;
    }

    // Ctrl/Alt/Super shortcuts: commit the word and let the application have
    // the key combination.
    if (states.testAny(
            KeyStates{KeyState::Ctrl, KeyState::Alt, KeyState::Super})) {
        handleIgnoredKey();
        return;
    }

    // Backspace: edit the preedit; forward to the app once it is empty.
    if (sym == FcitxKey_BackSpace) {
        if (preedit_.empty()) {
            commit();
            return; // not accepted -> forwarded to the application
        }
        vKeyHandleEvent(Keyboard, KeyDown, KEY_DELETE, 0, false);
        eraseLastChars(preedit_, 1);
        if (preedit_.empty()) {
            startNewSession();
        }
        updatePreedit();
        keyEvent.filterAndAccept();
        return;
    }

    // Navigation / editing keys: commit the word and forward the key.
    if (sym == FcitxKey_Tab || sym == FcitxKey_Return ||
        sym == FcitxKey_KP_Enter || sym == FcitxKey_Delete ||
        (sym >= FcitxKey_Home && sym <= FcitxKey_Insert) ||
        (sym >= FcitxKey_KP_Home && sym <= FcitxKey_KP_Delete)) {
        handleIgnoredKey();
        return;
    }

    // Printable ASCII: feed the engine and build the preedit.
    if (sym >= FcitxKey_space && sym <= FcitxKey_asciitilde) {
        const int caps = states.test(KeyState::Shift)
                             ? 1
                             : (states.test(KeyState::CapsLock) ? 2 : 0);
        const uint16_t code = keyEvent.rawKey().code();

        vKeyHandleEvent(Keyboard, KeyDown, code, caps, false);
        syncState(sym, code, caps);

        const bool wordBreak =
            (sym == FcitxKey_space) || (gHook->extCode == 1);
        if (wordBreak) {
            commit();
        } else {
            updatePreedit();
        }
        keyEvent.filterAndAccept();
        return;
    }

    // Anything else (dead keys, function keys, ...): commit and forward.
    handleIgnoredKey();
}

// ---------------------------------------------------------------------------
// OpenKeyEngine
// ---------------------------------------------------------------------------

OpenKeyEngine::OpenKeyEngine(Instance *instance)
    : instance_(instance), factory_([this](InputContext &ic) {
          return new OpenKeyState(this, &ic);
      }) {
    instance_->inputContextManager().registerProperty("openkey-state",
                                                       &factory_);
    gHook = static_cast<vKeyHookState *>(vKeyInit());
    reloadConfig();
}

OpenKeyEngine::~OpenKeyEngine() = default;

void OpenKeyEngine::keyEvent(const InputMethodEntry & /*entry*/,
                             KeyEvent &keyEvent) {
    auto *state = keyEvent.inputContext()->propertyFor(&factory_);
    state->keyEvent(keyEvent);
}

void OpenKeyEngine::activate(const InputMethodEntry & /*entry*/,
                             InputContextEvent &event) {
    event.inputContext()->propertyFor(&factory_)->reset();
}

void OpenKeyEngine::deactivate(const InputMethodEntry & /*entry*/,
                               InputContextEvent &event) {
    // Commit anything in flight so it is not lost when switching away.
    event.inputContext()->propertyFor(&factory_)->commit();
}

void OpenKeyEngine::reset(const InputMethodEntry & /*entry*/,
                          InputContextEvent &event) {
    event.inputContext()->propertyFor(&factory_)->reset();
}

void OpenKeyEngine::populateConfig() {
    vInputType = static_cast<int>(*config_.inputMethod);
    vCheckSpelling = *config_.spellCheck ? 1 : 0;
    vUseModernOrthography = *config_.modernOrthography ? 1 : 0;
    vFreeMark = *config_.freeMarking ? 1 : 0;
    vRestoreIfWrongSpelling = *config_.restoreIfWrongSpelling ? 1 : 0;
    vQuickTelex = *config_.quickTelex ? 1 : 0;
    vAllowConsonantZFWJ = *config_.allowConsonantZFWJ ? 1 : 0;
    vQuickStartConsonant = *config_.quickStartConsonant ? 1 : 0;
    vQuickEndConsonant = *config_.quickEndConsonant ? 1 : 0;
    vUpperCaseFirstChar = *config_.upperCaseFirstChar ? 1 : 0;
    vCodeTable = 0; // Unicode
    vLanguage = 1;  // Vietnamese
}

void OpenKeyEngine::reloadConfig() {
    readAsIni(config_, "conf/openkey.conf");
    populateConfig();
}

std::string OpenKeyEngine::subMode(const InputMethodEntry & /*entry*/,
                                   InputContext & /*inputContext*/) {
    return OpenKeyInputMethodI18NAnnotation::toString(*config_.inputMethod);
}

} // namespace fcitx

FCITX_ADDON_FACTORY_V2(openkey, fcitx::OpenKeyFactory)
