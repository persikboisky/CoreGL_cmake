//
// Created by kisly on 19.08.2025.
//

#ifndef VSWAPCHAIN_HPP
#define VSWAPCHAIN_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core::vulkan
{
    struct container;
    struct swapchain
    {
    private:
        static inline VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &formats);
        static inline VkPresentModeKHR chooseSwapPresentMode(
                const std::vector<VkPresentModeKHR> &presentModes,
                bool VerticalSynchronization);
        static inline VkImageView createImageView(
                container* cnt,
                const VkImage& image,
                VkFormat format,
                VkImageAspectFlags aspectFlags);

    public:
        static void create(container* cnt, bool VerticalSynchronization);
        static void destroy(container* cnt);
    };
}

#include "vSwapChain.inl"

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VSWAPCHAIN_HPP
