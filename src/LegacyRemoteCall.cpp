#include "LegacyRemoteCall.h"

#include "ll/api/mod/RegisterHelper.h"

namespace RemoteCall {
extern void removeAllFunc();
}
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

} // namespace legacy_remotecallapi

LL_REGISTER_MOD(legacy_remote_call_api::LegacyRemoteCallAPI, legacy_remote_call_api::LegacyRemoteCallAPI::getInstance());
