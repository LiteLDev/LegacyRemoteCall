#include "LegacyRemoteCall.h"

#include "ll/api/mod/NativeMod.h"
#include "ll/api/mod/RegisterHelper.h"

#include <memory>


namespace RemoteCall {
extern void removeAllFunc();
}
namespace legacy_remotecallapi {

static std::unique_ptr<LegacyRemoteCallAPI> instance;

LegacyRemoteCallAPI& LegacyRemoteCallAPI::getInstance() { return *instance; }

bool LegacyRemoteCallAPI::load() {
    getSelf().getLogger().info("Loading...");
    // Code for loading the plugin goes here.
    return true;
}

bool LegacyRemoteCallAPI::enable() {
    getSelf().getLogger().info("Enabling...");
    // Code for enabling the plugin goes here.
    return true;
}

bool LegacyRemoteCallAPI::disable() {
    getSelf().getLogger().info("Disabling...");
    // Code for disabling the plugin goes here.
    RemoteCall::removeAllFunc();
    return true;
}

} // namespace legacy_remotecallapi

LL_REGISTER_MOD(legacy_remotecallapi::LegacyRemoteCallAPI, legacy_remotecallapi::instance);
