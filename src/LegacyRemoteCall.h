#pragma once

#include "ll/api/mod/NativeMod.h"

namespace legacy_remote_call_api {

class LegacyRemoteCallAPI {

public:
    static LegacyRemoteCallAPI& getInstance();

    LegacyRemoteCallAPI() : mSelf(*ll::mod::NativeMod::current()) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();

private:
    ll::mod::NativeMod& mSelf;
};

} // namespace legacy_remotecallapi
