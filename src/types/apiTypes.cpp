//
// Created by kisly on 29.11.2025.
//

#include "apiTypes.hpp"
#if defined(CORE_INCLUDE_VULKAN)

VkFormat core::vulkan::convertFormat(const core::vulkan::FORMAT_VARIABLE& format)
{
	switch (format)
	{
	case vulkan::FLOAT:
		return VK_FORMAT_R32_SFLOAT;
	case vulkan::INT:
		return VK_FORMAT_R32_SINT;
	case vulkan::UINT:
		return VK_FORMAT_R32_UINT;
	case vulkan::VEC2:
		return VK_FORMAT_R32G32_SFLOAT;
	case vulkan::VEC3:
		return VK_FORMAT_R32G32B32_SFLOAT;
	case vulkan::VEC4:
		return VK_FORMAT_R32G32B32A32_SFLOAT;
	default:
		return VK_FORMAT_R32_SFLOAT;
	}
}
#endif //defined(CORE_INCLUDE_VULKAN)
