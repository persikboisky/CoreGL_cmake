//
// Created by kisly on 09.09.2025.
//

#ifndef RENDER_VK_QUEUE_HPP
#define RENDER_VK_QUEUE_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		enum class TypeFamilyQueue : int;

		struct SubmitInfo
		{
			std::vector<class CommandBuffer*> ptrCommandBuffer = {};
			std::vector<class Semaphore*> ptrWaitSemaphore = {};
			std::vector<class Semaphore*> ptrSignalSemaphore = {};
		    class Fence* ptrFence = nullptr;
		};

		struct PresentInfo
		{
			class Semaphore* ptrWaitSemaphore = nullptr;
			class SwapChain* ptrSwapChain = nullptr;
			uint32_t imageIndex = 0;
		};

		class Queue
		{
		private:
			VkQueue queue = nullptr;

			Queue(class Device &device, uint32_t queueFamilyIndex, uint32_t queueIndex);

		public:
		    ~Queue() = default;

			static Queue get(class Device& device, uint32_t queueFamilyIndex, uint32_t queueIndex);
			static Queue *ptrGet(class Device& device, uint32_t queueFamilyIndex, uint32_t queueIndex);

			void submit(SubmitInfo& info);
			void present(PresentInfo& info);
			void wait();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //RENDER_VK_QUEUE_HPP
