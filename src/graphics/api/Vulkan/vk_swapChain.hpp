//
// Created by kisly on 04.09.2025.
//

#ifndef VK_SWAPCHAIN_HPP
#define VK_SWAPCHAIN_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{ 
		struct SwapChainCreateInfo
		{
			/// @brief состояние верт.Синхронизации (true - включить, false - выключить)
			bool V_sync = true;

			/// @brief нужно ли обрезать (обрезать) отрисовываемое изображение, если оно частично перекрыто другими окнами
			bool clipped = true;

			/// @brief кол-во изображений в цепочке показа
			uint32_t countImage = 3;

			/// @brief указатель на холст(объект класса core::vulkan::Surface)
			class Surface *ptrSurface = nullptr;

			/// @brief указатель на логическое устройство(объект класса core::vulkan::Device)
			class Device *ptrDevice = nullptr;

			/// @brief предназначена ли цепочка показа для одной очереди(использование для одной очереди более производительное)
			bool exclusiveMode = true;

		    /// @brief список индексов семейств(нужно если выключен exclusiveMode)
		    std::vector<uint32_t> queueFamilyIndices = {};
		};

		/// @brief класс цепочки показа
		class SwapChain
		{
		protected:
			friend class FrameBuffer;
			friend class Queue;

		private:
			VkSwapchainKHR swapChain = {};
			VkDevice *ptrDevice = nullptr;

			std::vector<VkImageView> imagesView = {};

			SwapChain(const SwapChainCreateInfo& info);

		public:
			/// @brief создаёт цепочку показа
			/// @param info объект структуры core::vulkan::SwapChainCreateInfo
			/// @return возвращает объект core::vulkan::SwapChain
			static SwapChain create(const SwapChainCreateInfo &info);

			/// @brief создаёт цепочку показа
			/// @param info объект структуры core::vulkan::SwapChainCreateInfo
			/// @return возвращает указатель на объект core::vulkan::SwapChain
			static SwapChain *ptrCreate(const SwapChainCreateInfo &info);

			~SwapChain();

			/// @brief получает индекс следующего изображения из цепочке
			/// @param semaphore принимает семафор, который будет сигнализировать об удачном получении индекса
			/// @return возвращает индекс
			uint32_t getIndexNextImage(const class Semaphore& semaphore) const;

		    /// @brief получает индекс следующего изображения из цепочке
		    /// @param fence принимает fence, который будет сигнализировать об удачном получении индекса
		    /// @return возвращает индекс
		    uint32_t getIndexNextImage(const class Fence& fence) const;

		    /// @brief получает индекс следующего изображения из цепочке
		    /// @param semaphore принимает семафор, который будет сигнализировать об удачном получении индекса
		    /// @param fence принимает fence, который будет сигнализировать об удачном получении индекса
		    /// @return возвращает индекс
		    uint32_t getIndexNextImage(const class Semaphore& semaphore, const class Fence& fence) const;
		};
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
#endif // VK_SWAPCHAIN_HPP
