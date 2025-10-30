//
// Created by kisly on 11.09.2025.
//

#ifndef VK_GRAPHICSQUEUE_HPP_
#define VK_GRAPHICSQUEUE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct QueueSubmitInfo
		{
			class Semaphore *ptrWaitSemaphore = nullptr;
			class CommandBuffer *PtrCommandBuffer = nullptr;
			class Semaphore *ptrFinishSignalSemaphore = nullptr;
			class Fence *ptrFence = nullptr;
		};

		struct QueueSubmitsInfo
		{
			uint32_t countWaitSemaphores = 0;
			class Semaphore** ptrWaitSemaphores = nullptr;

			uint32_t countCommandBuffers = 0;
			class CommandBuffer** PtrCommandBuffers = nullptr;

			uint32_t countFinishSignalSemaphores = 0;
			class Semaphore** ptrFinishSignalSemaphores = nullptr;

			class Fence *ptrFence = nullptr;
		};

		struct QueuePresentInfo
		{
			class Semaphore *ptrWaitPtrSemaphore = nullptr;
			class SwapChain *ptrSwapChain = nullptr;
			uint32_t imageIndex = 0;
		};

		class Queue
		{
		 private:
			VkQueue queue;

			Queue(class Device& device, uint32_t queueIndex);

		 public:
			~Queue() = default;

			static Queue get(class Device& device, uint32_t queueIndex);
			static Queue ptrGet(class Device& device, uint32_t queueIndex);

			void submit(const QueueSubmitInfo& qs) const;
			void submits(const QueueSubmitsInfo& qs) const;
			void present(const QueuePresentInfo& qp) const;

			void wait() const;

			VkQueue getVkQueue() const;
			VkQueue *getVkPtrQueue();
		};
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
#endif //VK_GRAPHICSQUEUE_HPP_
