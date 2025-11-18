//
// Created by kisly on 01.09.2025.
//

#ifndef VK_INSTANCE_HPP_
#define VK_INSTANCE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/types.hpp"
#include <vulkan/vulkan.h>

namespace core::vulkan
{
	struct InstanceInfo
	{
		const char* appName = "CoreGL";
		version3 appVersion = { 1, 0, 0 };
		version3 vulkanVersion = { 1, 0, 0 };
	};

	class Instance
	{
	protected:
		friend class Surface;
		friend class PhysicalDevices;

	private:
		VkInstance instance = {};

		explicit Instance(const InstanceInfo& info);

	public:
		static Instance create(const InstanceInfo& info);
		static Instance *ptrCreate(const InstanceInfo& info);

		~Instance();
	};
}

#endif // defined(CORE_INCLUDE_VULKAN)
#endif // VK_INSTANCE_HPP_
