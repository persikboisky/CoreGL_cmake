//
// Created by kisly on 04.09.2025.
//

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../config.hpp"
#include "../../../util/Coders.hpp"
#include "../../../util/console.hpp"
#include "vk_Device.hpp"
#include "vk_PhysicalDevices.hpp"
#include "vk_Surface.hpp"
#include <array>
#include <iostream>
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		void Device::createImage(
				uint32_t width,
				uint32_t height,
				VkFormat format,
				VkImageUsageFlags usage,
				VkImage& image,
				VkDeviceMemory& imageMemory)
		{
			VkImageCreateInfo imageInfo{};
			imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			imageInfo.imageType = VK_IMAGE_TYPE_2D;
			imageInfo.extent.width = width;
			imageInfo.extent.height = height;
			imageInfo.extent.depth = 1;
			imageInfo.mipLevels = 1;
			imageInfo.arrayLayers = 1;
			imageInfo.format = format;
			imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
			imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			imageInfo.usage = usage;
			imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
			imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			if (vkCreateImage(this->device, &imageInfo, nullptr, &image) != VK_SUCCESS)
			{
				throw Coders(50);
			}

			VkMemoryRequirements memRequirements;
			vkGetImageMemoryRequirements(this->device, image, &memRequirements);

			VkMemoryAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = findMemoryType(
					memRequirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			if (vkAllocateMemory(this->device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
			{
				throw Coders(51);
			}

			vkBindImageMemory(this->device, image, imageMemory, 0);
		}

		VkImageView Device::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) const
        {
			VkImageViewCreateInfo viewInfo = {};
			viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			viewInfo.image = image;
			viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			viewInfo.format = format;
			viewInfo.subresourceRange.aspectMask = aspectFlags;
			viewInfo.subresourceRange.baseMipLevel = 0;
			viewInfo.subresourceRange.levelCount = 1;
			viewInfo.subresourceRange.baseArrayLayer = 0;
			viewInfo.subresourceRange.layerCount = 1;

			VkImageView imageView;
            const VkResult result = vkCreateImageView(this->device, &viewInfo, nullptr, &imageView);
			Coders::vulkanProcessingError(result);
			return imageView;
		}

		static inline VkFormat findSupportedFormat(
				const std::vector<VkFormat>& candidates,
				VkImageTiling tiling,
				VkFormatFeatureFlags features,
				VkPhysicalDevice* dev)
		{
			for (const VkFormat& format : candidates)
			{
				VkFormatProperties props;
				vkGetPhysicalDeviceFormatProperties(*dev, format, &props);

				if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
					return format;

				else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
					return format;

			}
			throw Coders(49);
		}

		static inline VkFormat findDepthFormat(VkPhysicalDevice* dev) {
			return findSupportedFormat(
					{VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
					VK_IMAGE_TILING_OPTIMAL,
					VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT,
					dev
			);
		}

		Device::Device(const DeviceCreateInfo& info) :
			physicalDevice(info.ptrPhDevices->devices[info.idPhDevice])
		{
			this->depthFormat = findDepthFormat(&this->physicalDevice);
			vkGetPhysicalDeviceProperties(this->physicalDevice, &this->deviceProperties);
			vkGetPhysicalDeviceFeatures(this->physicalDevice, &this->deviceFeatures);

			constexpr std::array<const char*, 1> enabledExtensionNames = {
					VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};

            const auto pQueueCreateInfos = new VkDeviceQueueCreateInfo[info.queueFamiliesInfo.size()];
		    for (uint32_t i = 0; i < info.queueFamiliesInfo.size(); i++)
		    {
		        pQueueCreateInfos[i] = {};
		        pQueueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		        pQueueCreateInfos[i].pNext = nullptr;
		        pQueueCreateInfos[i].flags = 0;
		        pQueueCreateInfos[i].queueFamilyIndex = info.queueFamiliesInfo[i].QueueFamilyIndex;
		        pQueueCreateInfos[i].queueCount = info.queueFamiliesInfo[i].QueueCount;
		        pQueueCreateInfos[i].pQueuePriorities = info.queueFamiliesInfo[i].QueuePriorities.data();
		    }

			VkDeviceCreateInfo deviceCreateInfo = {};
			deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(enabledExtensionNames.size());
			deviceCreateInfo.ppEnabledExtensionNames = enabledExtensionNames.data();
			deviceCreateInfo.flags = 0;
			deviceCreateInfo.pNext = nullptr;
			deviceCreateInfo.ppEnabledLayerNames = nullptr;
			deviceCreateInfo.enabledLayerCount = 0;
			deviceCreateInfo.pEnabledFeatures = &this->deviceFeatures;
			deviceCreateInfo.pQueueCreateInfos = pQueueCreateInfos;
			deviceCreateInfo.queueCreateInfoCount = info.queueFamiliesInfo.size();

			VkResult result = vkCreateDevice(
					this->physicalDevice,
					&deviceCreateInfo,
					nullptr,
					&this->device);
			Coders::vulkanProcessingError(result);

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "Ok: create vulkan device" << std::endl;
			}

			uint32_t count = 0;
			std::vector<VkSurfaceFormatKHR> surfaceFormats = {};
			result = vkGetPhysicalDeviceSurfaceFormatsKHR(
					this->physicalDevice,
					info.ptrSurface->surface,
					&count,
					nullptr);
			Coders::vulkanProcessingError(result);

			surfaceFormats.resize(count);
			result = vkGetPhysicalDeviceSurfaceFormatsKHR(
					this->physicalDevice,
					info.ptrSurface->surface,
					&count,
					surfaceFormats.data());
			Coders::vulkanProcessingError(result);

			for (const VkSurfaceFormatKHR& format: surfaceFormats)
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
					info.ptrSurface->surface,
					&this->surfaceCapabilitiesFormat);
			Coders::vulkanProcessingError(result);

		    delete[] pQueueCreateInfos;
		}

		Device Device::create(const DeviceCreateInfo& info)
		{
			return Device(info);
		}

		Device* Device::ptrCreate(const DeviceCreateInfo& info)
		{
			return new Device(info);
		}

		Device::~Device()
		{
			vkDestroyDevice(this->device, nullptr);
		}

		uint32_t Device::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const
        {
			VkPhysicalDeviceMemoryProperties memProperties;
			vkGetPhysicalDeviceMemoryProperties(this->physicalDevice, &memProperties);

			for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
				if ((typeFilter & (1 << i)) &&
					((memProperties.memoryTypes[i].propertyFlags & properties) == properties)) {
					return i;
				}
			}

			throw Coders(46);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)