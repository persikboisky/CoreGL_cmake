//
// Created by kisly on 04.09.2025.
//

#include "vk_physicalDevices.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Instance.hpp"
#include "../../../util/console.hpp"
#include "../../../util/coders.hpp"
#include "../../../config.hpp"
#include <iostream>

namespace core
{
	namespace vulkan
	{
		PhysicalDevices::PhysicalDevices(Instance& instance)
		{
			uint32_t count = 0;
			VkResult result = vkEnumeratePhysicalDevices(
				instance.instance,
				&count,
				nullptr);
			coders::vulkanProcessingError(result);

			this->devices.resize(count);

			result = vkEnumeratePhysicalDevices(
				instance.instance,
				&count,
				this->devices.data());
			coders::vulkanProcessingError(result);

			if (CORE_INFO)
			{
				count = 0;
				for (const VkPhysicalDevice& device : this->devices)
				{
					VkPhysicalDeviceProperties prop = {};
					vkGetPhysicalDeviceProperties(device, &prop);

					console::printTime();
					std::cout << "GPU [id: " << count << "] " << prop.deviceName << std::endl;

					count++;
				}
			}
		}

		PhysicalDevices PhysicalDevices::get(Instance& instance)
		{
			return PhysicalDevices(instance);
		}

		PhysicalDevices* PhysicalDevices::ptrGet(Instance& instance)
		{
			return new PhysicalDevices(instance);
		}

		[[maybe_unused]] VkPhysicalDevice PhysicalDevices::getVkPhysicalDevice(uint32_t id)
		{
			return this->devices[id];
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)