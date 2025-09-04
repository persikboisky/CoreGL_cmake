//
// Created by kisly on 04.09.2025.
//

#ifndef VK_PHYSICALDEVICES_HPP_
#define VK_PHYSICALDEVICES_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		class PhysicalDevices
		{
		 private:
			std::vector<VkPhysicalDevice> devices = {};

			explicit PhysicalDevices(class Instance& instance);

		 public:
			static PhysicalDevices get(class Instance& instance);
			static PhysicalDevices* ptrGet(class Instance& instance);

			[[maybe_unused]] VkPhysicalDevice getVkPhysicalDevice(uint32_t id = 0);

			~PhysicalDevices() = default;
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_PHYSICALDEVICES_HPP_
