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
		struct queueSubmitInfo
		{
			class Semaphore *waitPtrSemaphore = nullptr;
			class CommandBuffer *PtrCommandBuffer = nullptr;
			class Semaphore *finishSignalSemaphore = nullptr;
		};

		struct queuePresentInfo
		{
			class Semaphore *waitPtrSemaphore = nullptr;
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

			void submit(const queueSubmitInfo* qs);
			void present(const queuePresentInfo* qp);

			void wait();

			VkQueue getVkQueue();
			VkQueue *getVkPtrQueue();
		};
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
#endif //VK_GRAPHICSQUEUE_HPP_
