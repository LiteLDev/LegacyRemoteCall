#pragma once

#include "ll/api/mod/NativeMod.h"

namespace legacy_remotecallapi {

class LegacyRemoteCallAPI {

public:
    static LegacyRemoteCallAPI& getInstance();

    LegacyRemoteCallAPI(ll::mod::NativeMod& self) : mSelf(self) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();

    // bool unload();

private:
    ll::mod::NativeMod& mSelf;
};

} // namespace legacy_remotecallapi
