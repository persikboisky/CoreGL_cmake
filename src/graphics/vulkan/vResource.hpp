
#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core::vulkan
{
	struct apiContainer
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

        ~apiContainer();
	};

    struct piplineContainer
    {
        VkRenderPass renderPass;
        apiContainer *ptrApiContainer = nullptr;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        ~piplineContainer();
    };

    inline VkFormat findDepthFormat(const apiContainer& cnt);
    inline VkFormat findSupportedFormats(
            const apiContainer& cnt,
            const std::vector<VkFormat>& candidates,
            VkImageTiling tiling,
            VkFormatFeatureFlags features);
}

#include "vResource.inl"

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //!VRESOURCE_HPP
