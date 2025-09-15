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
		Device::Device(const deviceInfo& info) : physicalDevice(info.ptrPhDevices->getVkPhysicalDevice(info.idDevice))
		{
			vkGetPhysicalDeviceProperties(this->physicalDevice, &this->deviceProperties);
			vkGetPhysicalDeviceFeatures(this->physicalDevice, &this->deviceFeatures);

			std::vector<VkQueueFamilyProperties> queueFamilyProperties = {};
			uint32_t count = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(
					this->physicalDevice,
				&count,
				nullptr);
			queueFamilyProperties.resize(count);
			vkGetPhysicalDeviceQueueFamilyProperties(
					this->physicalDevice,
				&count,
				queueFamilyProperties.data());

			count = 0;
			for (const VkQueueFamilyProperties &prop : queueFamilyProperties)
			{
				if (prop.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					this->graphicsQueueFamilyIndex = count;
					this->countGraphicsQueue = prop.queueCount;
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
							this->physicalDevice,
						count,
						info.ptrSurface->getVkSurfaceKHR(),
						&flag);

					coders::vulkanProcessingError(result);
					if (flag == VK_TRUE)
					{
						this->presentQueueFamilyIndex = count;
						this->countPresentQueue = prop.queueCount;
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
					this->physicalDevice,
				&deviceCreateInfo,
				nullptr,
				&this->device);
			coders::vulkanProcessingError(result);

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "Ok: create vulkan device" << std::endl;
			}

			count = 0;
			std::vector<VkSurfaceFormatKHR> surfaceFormats = {};
			result = vkGetPhysicalDeviceSurfaceFormatsKHR(
					this->physicalDevice,
				info.ptrSurface->getVkSurfaceKHR(),
				&count,
				nullptr);
			coders::vulkanProcessingError(result);

			surfaceFormats.resize(count);
			result = vkGetPhysicalDeviceSurfaceFormatsKHR(
					this->physicalDevice,
				info.ptrSurface->getVkSurfaceKHR(),
				&count,
				surfaceFormats.data());
			coders::vulkanProcessingError(result);

			for (const VkSurfaceFormatKHR& format : surfaceFormats)
			{
				if (format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR &&
					format.format == VK_FORMAT_B8G8R8A8_UNORM)
				{
					this->surfaceFormat = format;
					break;
				}
			}

			result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
					this->physicalDevice,
				info.ptrSurface->getVkSurfaceKHR(),
				&this->surfaceCapabilitiesFormat);
			coders::vulkanProcessingError(result);
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

		uint32_t Device::getGraphicsQueueFamilyIndex()
		{
			return this->graphicsQueueFamilyIndex;
		}

		uint32_t Device::getPresentQueueFamilyIndex()
		{
			return this->presentQueueFamilyIndex;
		}

		VkSurfaceFormatKHR Device::getVkSurfaceFormat()
		{
			return this->surfaceFormat;
		}

		VkSurfaceCapabilitiesKHR Device::getVkSurfaceCapabilities()
		{
			return this->surfaceCapabilitiesFormat;
		}

		VkDevice Device::getDevice()
		{
			return this->device;
		}

		VkDevice* Device::getPtrDevice()
		{
			return &this->device;
		}

		uint32_t Device::getCountGraphicsQueue() const
		{
			return this->countGraphicsQueue;
		}

		uint32_t Device::getCountPresentQueue() const
		{
			return this->countPresentQueue;
		}

		uint32_t Device::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
		{
			VkPhysicalDeviceMemoryProperties memProperties;
			vkGetPhysicalDeviceMemoryProperties(this->physicalDevice, &memProperties);

			for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
				if ((typeFilter & (1 << i)) &&
					((memProperties.memoryTypes[i].propertyFlags & properties) == properties)) {
					return i;
				}
			}

			throw coders(46);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)