#pragma once

#include <ll/api/plugin/NativePlugin.h>

namespace LegacyRemoteCall {

class LegacyRemoteCall {
    LegacyRemoteCall();

public:
    LegacyRemoteCall(LegacyRemoteCall&&)                 = delete;
    LegacyRemoteCall(const LegacyRemoteCall&)            = delete;
    LegacyRemoteCall& operator=(LegacyRemoteCall&&)      = delete;
    LegacyRemoteCall& operator=(const LegacyRemoteCall&) = delete;

    static LegacyRemoteCall& getInstance();

    [[nodiscard]] ll::plugin::NativePlugin& getSelf() const;

    /// @return True if the plugin is loaded successfully.
    bool load(ll::plugin::NativePlugin&);

    /// @return True if the plugin is enabled successfully.
    bool enable();

    /// @return True if the plugin is disabled successfully.
    bool disable();

private:
    ll::plugin::NativePlugin* mSelf{};
};

} // namespace LegacyRemoteCall
