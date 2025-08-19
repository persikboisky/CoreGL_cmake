//
// Created by kisly on 06.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vResource.hpp"
#include <vulkan/vulkan.h>

namespace core::vulkan
{
    container::~container()
    {
        vkDestroyDevice(this->logicalDevice, nullptr);
        vkDestroySurfaceKHR(this->instance, this->surface, nullptr);
        vkDestroyInstance(this->instance, nullptr);
    }
}

#endif //defined(CORE_INCLUDE_VULKAN)

