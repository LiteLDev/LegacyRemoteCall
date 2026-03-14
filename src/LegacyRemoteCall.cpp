#include "LegacyRemoteCall.h"

#include "ll/api/mod/RegisterHelper.h"

namespace RemoteCall {
void removeAllFunc();
/*workaround to fix parallel_hashmap\phmap_base.h(1276): error C2332*/
ll::io::Logger& getLogger() { return legacy_remote_call_api::LegacyRemoteCallAPI::getInstance().getSelf().getLogger(); }
__declspec(dllexport) void _onCallError(std::string const& msg, void* handle) {
    getLogger().error(msg);
    auto plugin = ll::mod::NativeMod::getByHandle(handle);
    if (plugin) getLogger().error("In plugin <{}>", plugin->getManifest().name);
}
} // namespace RemoteCall
namespace legacy_remote_call_api {

LegacyRemoteCallAPI& LegacyRemoteCallAPI::getInstance() {
    static LegacyRemoteCallAPI instance;
    return instance;
}

bool LegacyRemoteCallAPI::load() { return true; }

bool LegacyRemoteCallAPI::enable() { return true; }

bool LegacyRemoteCallAPI::disable() {
    RemoteCall::removeAllFunc();
    return true;
}

} // namespace legacy_remote_call_api

LL_REGISTER_MOD(
    legacy_remote_call_api::LegacyRemoteCallAPI,
    legacy_remote_call_api::LegacyRemoteCallAPI::getInstance()
);
