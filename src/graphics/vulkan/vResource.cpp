//
// Created by kisly on 06.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vResource.hpp"
#include "vSurface.hpp"
#include <vulkan/vulkan.h>

namespace core::vulkan
{
    container::~container()
    {
        surface::destroy(this);
        vkDestroyInstance(this->instance, nullptr);
    }
}

#endif //defined(CORE_INCLUDE_VULKAN)

