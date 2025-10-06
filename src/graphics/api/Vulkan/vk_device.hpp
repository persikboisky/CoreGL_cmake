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
		/// @brief информация для создания vulkan::Device
		struct DeviceInfo
		{
			/// @brief указатель на объект класса vulkan::Instance
			class Instance* ptrInstance = nullptr;

			/// @brief указатель на объект класса vulkan::PhysicalDevices
			class PhysicalDevices* ptrPhDevices = nullptr;

			/// @brief указатель на объект класса vulkan::Surface
			class Surface* ptrSurface = nullptr;

			/// @brief индекс выбранной видиокарты согласно списку vulkan::PhysicalDevices
			unsigned int idDevice = 0;
		};

		class Device
		{
		 private:
			VkPhysicalDevice physicalDevice = {};
			VkDevice device = {};

			VkPhysicalDeviceProperties deviceProperties = {};
			VkPhysicalDeviceFeatures deviceFeatures = {};

			VkSurfaceFormatKHR surfaceFormat = {};
			VkSurfaceCapabilitiesKHR surfaceCapabilitiesFormat = {};

			uint32_t graphicsQueueFamilyIndex = 0;
			uint32_t presentQueueFamilyIndex = 0;

			uint32_t countGraphicsQueue = 0;
			uint32_t countPresentQueue = 0;

			const float queuePriorities = 1.0f;

			explicit Device(const DeviceInfo& info);

		 public:
			static Device create(const DeviceInfo& info);
			static Device* ptrCreate(const DeviceInfo& info);

			~Device();

			uint32_t getGraphicsQueueFamilyIndex();
			uint32_t getPresentQueueFamilyIndex();

			VkSurfaceFormatKHR getVkSurfaceFormat();
			VkSurfaceCapabilitiesKHR getVkSurfaceCapabilities();

			VkDevice getDevice();
			VkDevice *getPtrDevice();

			[[nodiscard]] uint32_t getCountGraphicsQueue() const;
			[[nodiscard]] uint32_t getCountPresentQueue() const;

			uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_DEVICE_HPP_
