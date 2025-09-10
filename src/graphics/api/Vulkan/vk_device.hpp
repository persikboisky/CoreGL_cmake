//
// Created by kisly on 04.09.2025.
//

#ifndef VK_DEVICE_HPP_
#define VK_DEVICE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct deviceInfo
		{
			class Instance* ptrInstance = nullptr;
			class PhysicalDevices* ptrPhDevices = nullptr;
			class Surface* ptrSurface = nullptr;
			unsigned int idDevice = 0;
		};

		class Device
		{
		 private:
			VkDevice device = {};
			VkPhysicalDeviceProperties deviceProperties = {};
			VkPhysicalDeviceFeatures deviceFeatures = {};
			VkCommandPool commandPool = {};

			VkSurfaceFormatKHR surfaceFormat = {};
			VkSurfaceCapabilitiesKHR surfaceCapabilitiesFormat = {};

			uint32_t graphicsQueueFamilyIndex = 0;
			uint32_t presentQueueFamilyIndex = 0;

			const float queuePriorities = 1.0f;

			explicit Device(const deviceInfo& info);

		 public:
			static Device create(const deviceInfo& info);
			static Device* ptrCreate(const deviceInfo& info);

			~Device();

			uint32_t getGraphicsQueueFamilyIndex();
			uint32_t getPresentQueueFamilyIndex();

			VkSurfaceFormatKHR getVkSurfaceFormat();
			VkSurfaceCapabilitiesKHR getVkSurfaceCapabilities();

			VkDevice getDevice();
			VkDevice *getPtrDevice();

			VkCommandPool getVkCommandPool();
			VkCommandPool *getVkPtrCommandPool();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_DEVICE_HPP_
