#include "LegacyRemoteCall.h"

#include "ll/api/mod/RegisterHelper.h"

#include <memory>
namespace RemoteCall {
extern void removeAllFunc();
}
namespace legacy_remotecallapi {

static std::unique_ptr<LegacyRemoteCallAPI> instance;

LegacyRemoteCallAPI& LegacyRemoteCallAPI::getInstance() { return *instance; }

bool LegacyRemoteCallAPI::load() { return true; }

bool LegacyRemoteCallAPI::enable() { return true; }

bool LegacyRemoteCallAPI::disable() {
    RemoteCall::removeAllFunc();
    return true;
}

} // namespace legacy_remotecallapi

LL_REGISTER_MOD(legacy_remotecallapi::LegacyRemoteCallAPI, legacy_remotecallapi::instance);
