
#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core::vulkan
{
    class SwapChain;
	struct container
	{
        VkInstance instance;
        VkSurfaceKHR surface;
        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;
        VkQueue graphicsQueue;
        VkSurfaceFormatKHR swapChainFormat;
        VkPresentModeKHR presentMode;
        VkExtent2D swapChainExtent;
        VkSwapchainKHR swapChain;

        std::vector<VkImageView> swapChainImagesViews = {};

        uint32_t graphicQueueFamilyIndex;
        uint32_t presentQueueFamilyIndex;

        const float _QueuePriorities = 1.0f;

        ~container();
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //!VRESOURCE_HPP
