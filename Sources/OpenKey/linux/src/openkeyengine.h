/*
 * OpenKey for Fcitx5 - input method engine.
 *
 * Thin glue that wraps OpenKey's platform independent C++ engine
 * (Sources/OpenKey/engine) as a Fcitx5 input method addon, following the
 * same pattern as fcitx5-unikey.
 */
#ifndef _FCITX5_OPENKEY_OPENKEYENGINE_H_
#define _FCITX5_OPENKEY_OPENKEYENGINE_H_

#include "openkeyconfig.h"
#include <fcitx-config/iniparser.h>
#include <fcitx-config/rawconfig.h>
#include <fcitx/addonfactory.h>
#include <fcitx/addoninstance.h>
#include <fcitx/addonmanager.h>
#include <fcitx/inputcontextproperty.h>
#include <fcitx/inputmethodengine.h>
#include <fcitx/instance.h>
#include <string>

namespace fcitx {

class OpenKeyState;

class OpenKeyEngine final : public InputMethodEngine {
public:
    explicit OpenKeyEngine(Instance *instance);
    ~OpenKeyEngine() override;

    Instance *instance() { return instance_; }
    auto &factory() { return factory_; }
    const OpenKeyConfig &config() const { return config_; }

    void keyEvent(const InputMethodEntry &entry, KeyEvent &keyEvent) override;
    void activate(const InputMethodEntry &entry,
                  InputContextEvent &event) override;
    void deactivate(const InputMethodEntry &entry,
                    InputContextEvent &event) override;
    void reset(const InputMethodEntry &entry,
               InputContextEvent &event) override;
    void reloadConfig() override;

    const Configuration *getConfig() const override { return &config_; }
    void setConfig(const RawConfig &config) override {
        config_.load(config, true);
        safeSaveAsIni(config_, "conf/openkey.conf");
        populateConfig();
    }

    std::string subMode(const InputMethodEntry &entry,
                        InputContext &inputContext) override;

private:
    // Copy the Fcitx5 config values into the engine's global v* variables.
    void populateConfig();

    OpenKeyConfig config_;
    Instance *instance_;
    FactoryFor<OpenKeyState> factory_;
};

class OpenKeyFactory : public AddonFactory {
public:
    AddonInstance *create(AddonManager *manager) override {
        return new OpenKeyEngine(manager->instance());
    }
};

} // namespace fcitx

#endif // _FCITX5_OPENKEY_OPENKEYENGINE_H_
