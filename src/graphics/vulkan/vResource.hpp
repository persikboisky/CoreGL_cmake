
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

        ~container();
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //!VRESOURCE_HPP
