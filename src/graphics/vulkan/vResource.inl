#include <vulkan/vulkan.h>
#include "../../util/coders.hpp"

inline VkFormat core::vulkan::findSupportedFormats(
        const apiContainer& cnt,
        const std::vector<VkFormat>& candidates,
        VkImageTiling tiling,
        VkFormatFeatureFlags features)
{
    for (VkFormat format : candidates)
    {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(cnt.physicalDevice, format, &props);

        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures &
                                                 features) == features)
        {
            return format;
        }
        else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.
                optimalTilingFeatures & features) == features)
        {
            return format;
        }
    }

    throw coders(41);
}

inline VkFormat core::vulkan::findDepthFormat(const apiContainer& cnt)
{
    return findSupportedFormats(cnt,
                                {
                                        VK_FORMAT_D32_SFLOAT,
                                        VK_FORMAT_D32_SFLOAT_S8_UINT,
                                        VK_FORMAT_D24_UNORM_S8_UINT
                                },
                                VK_IMAGE_TILING_OPTIMAL,
                                VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}