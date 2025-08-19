
#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core::vulkan
{
	struct container
	{
        VkInstance instance;
        VkSurfaceKHR surface;

        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;
        VkQueue graphicsQueue;

        uint32_t graphicQueueFamilyIndex;
        uint32_t presentQueueFamilyIndex;

        ~container();
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //!VRESOURCE_HPP
