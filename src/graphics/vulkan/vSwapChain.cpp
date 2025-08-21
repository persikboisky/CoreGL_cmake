//
// Created by kisly on 19.08.2025.
//

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>
#include "vSwapChain.hpp"
#include "vResource.hpp"
#include "../../util/coders.hpp"

namespace core::vulkan
{
    void swapchain::create(container *cnt, bool VerticalSynchronization)
    {
////////////////////////////////////////////////////////////
// формат изображения
////////////////////////////////////////////////////////////
        uint32_t formatCount;
        std::vector<VkSurfaceFormatKHR> formats;

        VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(
                cnt->physicalDevice,
                cnt->surface,
                &formatCount,
                nullptr);
        coders::vulkanProcessingError(result);

        if (formatCount != 0)
        {
            formats.resize(formatCount);
            result = vkGetPhysicalDeviceSurfaceFormatsKHR(
                    cnt->physicalDevice,
                    cnt->surface,
                    &formatCount,
                    formats.data());
            coders::vulkanProcessingError(result);
        }
        else coders(38, "Function: void swapchain::create(container *cnt)");

        cnt->swapChainFormat = chooseSurfaceFormat(formats);

////////////////////////////////////////////////////////////
// режим показа
////////////////////////////////////////////////////////////
        uint32_t presentModeCount;
        std::vector<VkPresentModeKHR> presentModes;

        vkGetPhysicalDeviceSurfacePresentModesKHR(
                cnt->physicalDevice,
                cnt->surface,
                &presentModeCount,
                nullptr);

        if (presentModeCount != 0)
        {
            presentModes.resize(presentModeCount);
            result = vkGetPhysicalDeviceSurfacePresentModesKHR(
                    cnt->physicalDevice,
                    cnt->surface,
                    &presentModeCount,
                    presentModes.data());
            coders::vulkanProcessingError(result);
        }
        else coders(39, "Function: void swapchain::create(container *cnt)");

        cnt->presentMode = chooseSwapPresentMode(presentModes, VerticalSynchronization);

////////////////////////////////////////////////////////////
// получаем capabilities
////////////////////////////////////////////////////////////
        VkSurfaceCapabilitiesKHR capabilities;

        result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
                cnt->physicalDevice,
                cnt->surface,
                &capabilities);
        coders::vulkanProcessingError(result);

        cnt->swapChainExtent = capabilities.currentExtent;

////////////////////////////////////////////////////////////
// создаём swapchain
////////////////////////////////////////////////////////////
        VkSwapchainCreateInfoKHR swapChainInfo = {};
        swapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapChainInfo.pNext = nullptr;
        swapChainInfo.flags = 0;
        swapChainInfo.surface = cnt->surface;
        swapChainInfo.imageFormat = cnt->swapChainFormat.format;
        swapChainInfo.imageColorSpace = cnt->swapChainFormat.colorSpace;
        swapChainInfo.presentMode = cnt->presentMode;
        swapChainInfo.minImageCount = capabilities.minImageCount + 1;         // кол-во изображений в буфере
        swapChainInfo.imageExtent = capabilities.currentExtent;
        swapChainInfo.preTransform = capabilities.currentTransform;
        swapChainInfo.imageArrayLayers = 1;
        swapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapChainInfo.queueFamilyIndexCount = 0;
        swapChainInfo.pQueueFamilyIndices = nullptr;
        swapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapChainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapChainInfo.clipped = VK_TRUE;
        swapChainInfo.oldSwapchain = nullptr;

        result = vkCreateSwapchainKHR(
                cnt->logicalDevice,
                &swapChainInfo,
                nullptr,
                &cnt->swapChain);
        coders::vulkanProcessingError(result);

        uint32_t swapImageCount;

        result = vkGetSwapchainImagesKHR(
                cnt->logicalDevice,
                cnt->swapChain,
                &swapImageCount,
                nullptr);
        coders::vulkanProcessingError(result);

        std::vector<VkImage> images;
        images.resize(swapImageCount);

        result = vkGetSwapchainImagesKHR(
                cnt->logicalDevice,
                cnt->swapChain,
                &swapImageCount,
                images.data());
        coders::vulkanProcessingError(result);

        cnt->swapChainImagesViews.resize(swapImageCount);

        for (int i = 0; i < swapImageCount; i++)
        {
            cnt->swapChainImagesViews[i] = createImageView(
                    cnt,
                    images[i],
                    swapChainInfo.imageFormat,
                    VK_IMAGE_ASPECT_COLOR_BIT);
            coders::vulkanProcessingError(result);
        }
    }

    void swapchain::destroy(container *cnt)
    {
        for (const VkImageView &imageView : cnt->swapChainImagesViews)
        {
            vkDestroyImageView(cnt->logicalDevice, imageView, nullptr);
        }
        vkDestroySwapchainKHR(cnt->logicalDevice, cnt->swapChain, nullptr);
    }
}

#endif //defined(CORE_INCLUDE_VULKAN)