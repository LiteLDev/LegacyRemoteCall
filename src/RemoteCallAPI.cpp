#include "RemoteCallAPI.h"

#include "LegacyRemoteCall.h"
#include "ll/api/io/Logger.h"
#include "ll/api/utils/StringUtils.h"


namespace RemoteCall {
ll::io::Logger& getLogger() { return legacy_remote_call_api::LegacyRemoteCallAPI::getInstance().getSelf().getLogger(); }
struct TransparentHasher {
    using is_transparent = void;
    auto operator()(const std::string& key) const { return std::hash<std::string>{}(key); }
    auto operator()(std::string_view key) const { return std::hash<std::string_view>{}(key); }
    auto operator()(const char* key) const { return std::hash<std::string_view>{}(key); }
};
CallbackFn const                                                                                  EMPTY_FUNC{};
std::unordered_map<std::string, RemoteCall::ExportedFuncData, TransparentHasher, std::equal_to<>> exportedFuncs;
bool exportFunc(std::string const& nameSpace, std::string const& funcName, CallbackFn&& callback, void* handle) {
    if (nameSpace.find("::") != std::string::npos) {
        getLogger().error("Namespace can't includes \"::\"");
        return false;
    }
    if (exportedFuncs.count(nameSpace + "::" + funcName) != 0) return false;
    exportedFuncs.emplace(nameSpace + "::" + funcName, ExportedFuncData{handle, std::move(callback)});
    return true;
}

CallbackFn const& importFunc(std::string const& nameSpace, std::string const& funcName) {
    auto iter = exportedFuncs.find(nameSpace + "::" + funcName);
    if (iter == exportedFuncs.end()) return EMPTY_FUNC;
    return iter->second.callback;
}

bool hasFunc(std::string const& nameSpace, std::string const& funcName) {
    return exportedFuncs.find(nameSpace + "::" + funcName) != exportedFuncs.end();
}

bool removeFunc(std::string_view key) {
    if (auto iter = exportedFuncs.find(key); iter != exportedFuncs.end()) {
        exportedFuncs.erase(iter);
        return true;
    }
    return false;
}

bool removeFunc(std::string const& nameSpace, std::string const& funcName) {
    return removeFunc(nameSpace + "::" + funcName);
}

int removeNameSpace(std::string const& nameSpace) {
    int count = 0;
    for (auto iter = exportedFuncs.begin(); iter != exportedFuncs.end();) {
        if (ll::string_utils::splitByPattern(iter->first, "::")[0] == nameSpace) {
            iter = exportedFuncs.erase(iter);
            ++count;
        } else ++iter;
    }
    return count;
}

int removeFuncs(std::vector<std::pair<std::string, std::string>>& funcs) {
    int count = 0;
    for (auto& [ns, name] : funcs) {
        if (removeFunc((ns + "::").append(name))) count++;
    }
    return count;
}

void removeAllFunc() { exportedFuncs.clear(); }

void _onCallError(std::string const& msg, void* handle) {
    getLogger().error(msg);
    auto plugin = ll::mod::NativeMod::getByHandle(handle);
    if (plugin) getLogger().error("In plugin <{}>", plugin->getManifest().name);
}
} // namespace RemoteCall

static_assert(RemoteCall::is_supported_type_v<void>);
static_assert(RemoteCall::is_supported_type_v<int>);
static_assert(RemoteCall::is_supported_type_v<bool>);
static_assert(RemoteCall::is_supported_type_v<float>);
static_assert(RemoteCall::is_supported_type_v<size_t>);
static_assert(RemoteCall::is_supported_type_v<Player*>);
static_assert(RemoteCall::is_supported_type_v<Actor*>);
static_assert(RemoteCall::is_supported_type_v<Mob*>);
static_assert(RemoteCall::is_supported_type_v<BlockActor*>);
static_assert(RemoteCall::is_supported_type_v<Block*>);
static_assert(RemoteCall::is_supported_type_v<Vec3>);
static_assert(RemoteCall::is_supported_type_v<Vec3&>);
static_assert(RemoteCall::is_supported_type_v<Vec3 const&>);
// static_assert(RemoteCall::is_supported_type_v<Vec3 const*>);
static_assert(RemoteCall::is_supported_type_v<CompoundTag*>);