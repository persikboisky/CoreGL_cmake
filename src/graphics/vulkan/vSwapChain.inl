#include "vSwapChain.hpp"
#include "vResource.hpp"
#include "../../util/coders.hpp"
#include <iostream>

inline VkSurfaceFormatKHR core::vulkan::swapchain::chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &formats)
{
    for (const VkSurfaceFormatKHR& format : formats)
    {
        if (format.format == VK_FORMAT_B8G8R8A8_SRGB &&
        format.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR) return format;
    }

    return formats[0];
}

inline VkPresentModeKHR core::vulkan::swapchain::chooseSwapPresentMode(
        const std::vector<VkPresentModeKHR> &presentModes,
        bool VerticalSynchronization)
{
    for (const VkPresentModeKHR& mode : presentModes)
    {
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
            return mode;
    }

    // верт.сихрон
    return VK_PRESENT_MODE_FIFO_KHR;
}

inline VkImageView core::vulkan::swapchain::createImageView(
        apiContainer* cnt,
        const VkImage& image,
        VkFormat format,
        VkImageAspectFlags aspectFlags)
{
    VkImageView imageView;

    VkImageViewCreateInfo imageViewInfo = {};
    imageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewInfo.flags = 0;
    imageViewInfo.pNext = nullptr;
    imageViewInfo.format = format;
    imageViewInfo.image = image;
    imageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewInfo.subresourceRange.aspectMask = aspectFlags;
    imageViewInfo.subresourceRange.levelCount = 1;
    imageViewInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(
            cnt->logicalDevice,
            &imageViewInfo,
            nullptr,
            &imageView) != VK_SUCCESS) throw coders(40);

    return imageView;
}
