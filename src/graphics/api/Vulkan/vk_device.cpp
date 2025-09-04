//
// Created by kisly on 04.09.2025.
//

#include "vk_device.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Instance.hpp"
#include "vk_physicalDevices.hpp"
#include "vk_surface.hpp"
#include "../../../util/coders.hpp"
#include "../../../util/console.hpp"
#include "../../../config.hpp"
#include <vector>
#include <array>
#include <iostream>

namespace core
{
	namespace vulkan
	{
		Device::Device(const deviceInfo& info)
		{
			VkPhysicalDevice phDevice = info.ptrPhDevices->getVkPhysicalDevice(info.idDevice);
			vkGetPhysicalDeviceProperties(phDevice, &this->deviceProperties);
			vkGetPhysicalDeviceFeatures(phDevice, &this->deviceFeatures);

			std::vector<VkQueueFamilyProperties> queueFamilyProperties = {};
			uint32_t count = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(
				phDevice,
				&count,
				nullptr);
			queueFamilyProperties.resize(count);
			vkGetPhysicalDeviceQueueFamilyProperties(
				phDevice,
				&count,
				queueFamilyProperties.data());

			count = 0;
			for (const VkQueueFamilyProperties &prop : queueFamilyProperties)
			{
				if (prop.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					this->graphicsQueueFamilyIndex = count;
					break;
				}
				count++;
			}

			count = 0;
			for (const VkQueueFamilyProperties &prop : queueFamilyProperties)
			{
				if (prop.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					VkBool32 flag = VK_FALSE;
					VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(
						phDevice,
						count,
						info.ptrSurface->getVkSurfaceKHR(),
						&flag);

					coders::vulkanProcessingError(result);
					if (flag == VK_TRUE)
					{
						this->presentQueueFamilyIndex = count;
						break;
					}
				}
				count++;
			}

			std::array<const char*, 1> enabledExtensionNames = {
				VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};

			VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
			deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			deviceQueueCreateInfo.pNext = nullptr;
			deviceQueueCreateInfo.flags = 0;
			deviceQueueCreateInfo.queueFamilyIndex = this->graphicsQueueFamilyIndex;
			deviceQueueCreateInfo.queueCount = 1;
			deviceQueueCreateInfo.pQueuePriorities = &this->queuePriorities;

			VkDeviceCreateInfo deviceCreateInfo = {};
			deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(enabledExtensionNames.size());
			deviceCreateInfo.ppEnabledExtensionNames = enabledExtensionNames.data();
			deviceCreateInfo.flags = 0;
			deviceCreateInfo.pNext = nullptr;
			deviceCreateInfo.ppEnabledLayerNames = nullptr;
			deviceCreateInfo.enabledLayerCount = 0;
			deviceCreateInfo.pEnabledFeatures = &this->deviceFeatures;
			deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
			deviceCreateInfo.queueCreateInfoCount = 1;

			VkResult result = vkCreateDevice(
				phDevice,
				&deviceCreateInfo,
				nullptr,
				&this->device);
			coders::vulkanProcessingError(result);

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "Ok: create vulkan device" << std::endl;
			}
		}

		Device Device::create(const deviceInfo& info)
		{
			return Device(info);
		}

		Device* Device::ptrCreate(const deviceInfo& info)
		{
			return new Device(info);
		}

		Device::~Device()
		{
			vkDestroyDevice(this->device, nullptr);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)