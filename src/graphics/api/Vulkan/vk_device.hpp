//
// Created by kisly on 04.09.2025.
//

#ifndef VK_DEVICE_HPP
#define VK_DEVICE_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		enum class TypeFamilyQueue : int
		{
			GRAPHICS,
			PRESENT,
			COMPUTER,
			TRANSFER
		};

		struct DeviceExtensionsInfo
		{

		};

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
			unsigned int idPhDevice = 0;

			DeviceExtensionsInfo* ptrDeviceExtensionsInfo = nullptr;
		};

		class Device
		{
		protected:
			friend class Image;
			friend class Queue;
			friend class Buffer;
			friend class SwapChain;
			friend class Semaphore;
			friend class RenderPass;
			friend class FrameBuffer;
			friend class CommandPool;
			friend class VertexBuffer;
			friend class ShaderModule;
			friend class DescriptorSet;
			friend class ElementBuffer;
			friend class CommandBuffer;
			friend class DescriptorPool;
			friend class PipelineLayout;
			friend class GraphicsPipeline;
			friend class DescriptorSetLayout;

		private:
			VkPhysicalDevice physicalDevice = {};
			VkDevice device = {};

			VkPhysicalDeviceProperties deviceProperties = {};
			VkPhysicalDeviceFeatures deviceFeatures = {};
			VkSurfaceFormatKHR surfaceFormat = {};
			VkSurfaceCapabilitiesKHR surfaceCapabilitiesFormat = {};

			VkFormat depthFormat = {};

			uint32_t graphicsQueueFamilyIndex = 0;
			uint32_t presentQueueFamilyIndex = 0;
			uint32_t computeFamilyIndex = 0;
			uint32_t transferFamilyIndex = 0;

			uint32_t countGraphicsQueue = 0;
			uint32_t countPresentQueue = 0;
			uint32_t countComputeQueue = 0;
			uint32_t countTransferQueue = 0;

			const float queuePriorities = 1.0f;

			explicit Device(const DeviceInfo& info);

			uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
			void createImage(
					uint32_t width,
					uint32_t height,
					VkFormat format,
					VkImageUsageFlags usage,
					VkImage& image,
					VkDeviceMemory& imageMemory);

			VkImageView createImageView(
					VkImage image,
					VkFormat format,
					VkImageAspectFlags aspectFlags);

		public:
			static Device create(const DeviceInfo& info);
			static Device* ptrCreate(const DeviceInfo& info);

			~Device();

			uint32_t getGraphicsQueueFamilyIndex() const;
			uint32_t getPresentQueueFamilyIndex() const;

			[[nodiscard]] uint32_t getCountGraphicsQueue() const;
			[[nodiscard]] uint32_t getCountPresentQueue() const;

			uint32_t getQueueFamilyIndex(const TypeFamilyQueue& type) const;
			uint32_t getCountQueue(const TypeFamilyQueue& type) const;
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_DEVICE_HPP
