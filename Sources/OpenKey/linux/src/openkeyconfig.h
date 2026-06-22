/*
 * OpenKey for Fcitx5 - configuration descriptor.
 *
 * These options are rendered automatically by fcitx5-configtool and are
 * copied into the engine's global `v*` variables by
 * OpenKeyEngine::populateConfig().
 */
#ifndef _FCITX5_OPENKEY_OPENKEYCONFIG_H_
#define _FCITX5_OPENKEY_OPENKEYCONFIG_H_

#include <fcitx-config/configuration.h>
#include <fcitx-config/enum.h>
#include <fcitx-config/option.h>
#include <fcitx-utils/i18n.h>

namespace fcitx {

// Order matches the engine's vKeyInputType enum (Telex=0, VNI=1, ...).
enum class OpenKeyInputMethod { Telex, VNI, SimpleTelex1, SimpleTelex2 };

FCITX_CONFIG_ENUM_NAME_WITH_I18N(OpenKeyInputMethod, N_("Telex"), N_("VNI"),
                                 N_("Simple Telex 1"), N_("Simple Telex 2"));

FCITX_CONFIGURATION(
    OpenKeyConfig,
    OptionWithAnnotation<OpenKeyInputMethod, OpenKeyInputMethodI18NAnnotation>
        inputMethod{this, "InputMethod", _("Input method"),
                    OpenKeyInputMethod::Telex};
    Option<bool> spellCheck{this, "SpellCheck", _("Check spelling"), true};
    Option<bool> modernOrthography{
        this, "ModernOrthography", _("Modern tone placement (oà, uý)"), true};
    Option<bool> freeMarking{this, "FreeMarking",
                             _("Allow tone marks to be typed anywhere"), true};
    Option<bool> restoreIfWrongSpelling{
        this, "RestoreIfWrongSpelling",
        _("Restore keystrokes for non-Vietnamese words"), true};
    Option<bool> quickTelex{
        this, "QuickTelex", _("Quick Telex (cc=ch, gg=gi, …)"), false};
    Option<bool> allowConsonantZFWJ{
        this, "AllowConsonantZFWJ", _("Allow Z, F, W, J as consonants"), false};
    Option<bool> quickStartConsonant{
        this, "QuickStartConsonant",
        _("Quick start consonant (f→ph, j→gi, w→qu)"), false};
    Option<bool> quickEndConsonant{
        this, "QuickEndConsonant",
        _("Quick end consonant (g→ng, h→nh, k→ch)"), false};
    Option<bool> upperCaseFirstChar{
        this, "CapitalizeFirstChar",
        _("Capitalize the first letter of a sentence"), false};
    Option<bool> displayUnderline{
        this, "DisplayUnderline", _("Underline the text being composed"),
        true};);

} // namespace fcitx

#endif // _FCITX5_OPENKEY_OPENKEYCONFIG_H_
