//
// Created by kisly on 06.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vResource.hpp"
#include "vSurface.hpp"
#include "vRenderPass.hpp"
#include <vulkan/vulkan.h>

namespace core::vulkan
{
    apiContainer::~apiContainer()
    {
        surface::destroy(this);
        vkDestroyInstance(this->instance, nullptr);
    }

    piplineContainer::~piplineContainer()
    {
        renderPass::destroy(this, *this->ptrApiContainer);
    }
}

#endif //defined(CORE_INCLUDE_VULKAN)

