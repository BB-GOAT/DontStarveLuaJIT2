#pragma once
// render.angle domain helper — read cascade AngleBackend without L0 accessors.
#include "AngleOptionKeys.hpp"
#include "config/ResolvedConfig.hpp"

#include <string_view>

namespace ds::render_angle {

inline std::string_view angle_backend(const ds::config::ResolvedConfig &rc) {
    auto it = rc.view.find(std::string{ds::config::keys::kAngleBackend});
    if (it != rc.view.end() && it->second.type == ds::plugin::ConfigValueType::String &&
        !it->second.s.empty()) {
        return it->second.s;
    }
    return "auto";
}

// VulkanOverlayCompat（默认开启）：Vulkan 后端下保持 Steam 覆盖层可用。
// 开启时禁用 ANGLE 的 supportsSwapchainMaintenance1 特性（Steam 覆盖层 Vulkan layer
// 不能处理 maintenance1 的 present fence / 延迟释放交换链结构，覆盖层激活会导致
// 呈现失败并卡死渲染线程），并且不再向 VK_LOADER_LAYERS_DISABLE 写入禁用项。
inline bool vulkan_overlay_compat(const ds::config::ResolvedConfig &rc) {
    auto it = rc.view.find(std::string{ds::config::keys::kVulkanOverlayCompat});
    if (it != rc.view.end() && it->second.type == ds::plugin::ConfigValueType::Bool) {
        return it->second.b;
    }
    return true;
}

} // namespace ds::render_angle
