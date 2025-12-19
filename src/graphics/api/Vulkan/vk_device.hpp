//
// Created by kisly on 04.09.2025.
//

#ifndef VK_DEVICE_HPP
#define VK_DEVICE_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

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

	    /// @brief струтура для описания используемых очередей
	    struct DeviceQueueFamilyInfo
	    {
            /// @brief индекс семейства
            uint32_t QueueFamilyIndex = 0;

	        /// @brief кол-во очередей для использования из семейства
	        uint32_t QueueCount = 0;

	        /// @brief приорететы очередей
	        std::vector<float> QueuePriorities = {};
	    };

		/// @brief информация для создания core::vulkan::Device
		struct DeviceCreateInfo
		{
			/// @brief указатель на объект класса core::vulkan::Instance
			class Instance* ptrInstance = nullptr;

			/// @brief указатель на объект класса core::vulkan::PhysicalDevices
			class PhysicalDevices* ptrPhDevices = nullptr;

			/// @brief указатель на объект класса core::vulkan::Surface
			class Surface* ptrSurface = nullptr;

			/// @brief индекс выбранной видеокарты согласно списку core::vulkan::PhysicalDevices
			unsigned int idPhDevice = 0;

			DeviceExtensionsInfo* ptrDeviceExtensionsInfo = nullptr;

		    /// @brief вектор перечесления объектов структуры core::vulkan::DeviceQueueFamilyInfo
		    std::vector<DeviceQueueFamilyInfo> queueFamiliesInfo = {};
		};

		/// @brief класс логического устройства vulkan(контекст)
		class Device
		{
		protected:
			friend class Image;
			friend class Queue;
		    friend class Fence;
			friend class Buffer;
			friend class Sampler;
			friend class SwapChain;
			friend class ImageView;
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
		    friend class ComputePipeline;
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

			explicit Device(const DeviceCreateInfo& info);

			uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
			void createImage(
					uint32_t width,
					uint32_t height,
					VkFormat format,
					VkImageUsageFlags usage,
					VkImage& image,
					VkDeviceMemory& imageMemory);
            VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) const;

		public:
			/// @brief функция для создания логического устройства
			/// @param info объект структуры core::vulkan::DeviceCreateInfo
			/// @return объект класса core::vulkan::Device
			static Device create(const DeviceCreateInfo& info);

			/// @brief функция для создания логического устройства
			/// @param info объект структуры core::vulkan::DeviceCreateInfo
			/// @return указатель на объект класса core::vulkan::Device
			static Device* ptrCreate(const DeviceCreateInfo& info);

			~Device();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_DEVICE_HPP