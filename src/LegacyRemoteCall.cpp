#include "LegacyRemoteCall.h"

#include <ll/api/plugin/NativePlugin.h>
#include <memory>

namespace RemoteCall {
extern void removeAllFunc();
}

namespace LegacyRemoteCall {

LegacyRemoteCall::LegacyRemoteCall() = default;

LegacyRemoteCall& LegacyRemoteCall::getInstance() {
    static LegacyRemoteCall instance;
    return instance;
}

ll::plugin::NativePlugin& LegacyRemoteCall::getSelf() const { return *mSelf; }

bool LegacyRemoteCall::load(ll::plugin::NativePlugin& self) {
    mSelf = std::addressof(self);
    getSelf().getLogger().info("loading...");
    return true;
}

bool LegacyRemoteCall::enable() { return true; }

bool LegacyRemoteCall::disable() {
    RemoteCall::removeAllFunc();
    return true;
}

extern "C" {
_declspec(dllexport) bool ll_plugin_load(ll::plugin::NativePlugin& self) {
    return LegacyRemoteCall::getInstance().load(self);
}

_declspec(dllexport) bool ll_plugin_enable(ll::plugin::NativePlugin&) {
    return LegacyRemoteCall::getInstance().enable();
}

_declspec(dllexport) bool ll_plugin_disable(ll::plugin::NativePlugin&) {
    return LegacyRemoteCall::getInstance().disable();
}

/// @warning Unloading the plugin may cause a crash if the plugin has not released all of its
/// resources. If you are unsure, keep this function commented out.
// _declspec(dllexport) bool ll_plugin_unload(ll::plugin::NativePlugin&) {
//     return LegacyRemoteCall::getInstance().unload();
// }
}

} // namespace LegacyRemoteCall
