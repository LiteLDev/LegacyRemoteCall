#include "LegacyRemoteCall.h"

#include "ll/api/mod/RegisterHelper.h"

namespace RemoteCall {
void removeAllFunc();
} // namespace RemoteCall
namespace legacy_remote_call_api {

LegacyRemoteCallAPI& LegacyRemoteCallAPI::getInstance() {
    static LegacyRemoteCallAPI instance;
    return instance;
}

bool LegacyRemoteCallAPI::load() /*NOLINT*/ { return true; }

bool LegacyRemoteCallAPI::enable() /*NOLINT*/ { return true; }

bool LegacyRemoteCallAPI::disable() /*NOLINT*/ {
    RemoteCall::removeAllFunc();
    return true;
}

} // namespace legacy_remote_call_api

LL_REGISTER_MOD(
    legacy_remote_call_api::LegacyRemoteCallAPI,
    legacy_remote_call_api::LegacyRemoteCallAPI::getInstance()
);
