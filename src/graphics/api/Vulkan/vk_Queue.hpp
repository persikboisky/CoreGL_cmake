//
// Created by kisly on 09.09.2025.
//

#ifndef RENDER_VK_QUEUE_HPP
#define RENDER_VK_QUEUE_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		enum class TypeFamilyQueue : int;

		struct SubmitInfo
		{
			class CommandBuffer* ptrCommandBuffer = nullptr;
			class Semaphore* ptrWaitSemaphore = nullptr;
			class Semaphore* ptrSignalSemaphore = nullptr;
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
			VkQueue queue = {};

			Queue(class Device& device, uint32_t index);

		public:
			static Queue create(class Device& device, const TypeFamilyQueue& type);
			static Queue *ptrCreate(class Device& device, const TypeFamilyQueue& type);

			void submit(SubmitInfo& info);
			void present(PresentInfo& info);
			void wait();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //RENDER_VK_QUEUE_HPP
