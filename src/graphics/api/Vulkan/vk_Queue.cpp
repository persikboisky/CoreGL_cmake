//
// Created by kisly on 09.09.2025.
//

#include "vk_Queue.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/Coders.hpp"
#include "vk_CommandBuffer.hpp"
#include "vk_Device.hpp"
#include "vk_Semaphore.hpp"
#include "vk_SwapChain.hpp"

namespace core
{
	namespace vulkan
	{
		Queue::Queue(Device& device, uint32_t index)
		{
			vkGetDeviceQueue(
					device.device,
					index,
					0,
					&this->queue);
		}

		Queue Queue::create(Device& device, const TypeFamilyQueue& type)
		{
			return Queue(device, device.getQueueFamilyIndex(type));
		}

		Queue* Queue::ptrCreate(Device& device, const TypeFamilyQueue& type)
		{
			return new Queue(device, device.getQueueFamilyIndex(type));
		}

		void Queue::submit(SubmitInfo& info)
		{
			VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
			VkSubmitInfo submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.pNext = nullptr;
			submitInfo.pCommandBuffers = &info.ptrCommandBuffer->commandBuffer;
			submitInfo.commandBufferCount = 1;
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.pSignalSemaphores = (info.ptrSignalSemaphore != nullptr) ? &info.ptrSignalSemaphore->semaphore : nullptr;
			submitInfo.signalSemaphoreCount = (info.ptrSignalSemaphore != nullptr) ? 1 : 0;
			submitInfo.pWaitSemaphores = (info.ptrWaitSemaphore != nullptr) ? &info.ptrWaitSemaphore->semaphore : nullptr;
			submitInfo.waitSemaphoreCount = (info.ptrWaitSemaphore != nullptr) ? 1 : 0;

			vkQueueSubmit(this->queue, 1, &submitInfo, VK_NULL_HANDLE);
		}

		void Queue::present(PresentInfo& info)
		{
			VkPresentInfoKHR presentInfoKhr = {};
			presentInfoKhr.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfoKhr.waitSemaphoreCount = 1;
			presentInfoKhr.pWaitSemaphores = &info.ptrWaitSemaphore->semaphore;
			presentInfoKhr.pNext = nullptr;
			presentInfoKhr.pResults = nullptr;
			presentInfoKhr.swapchainCount = 1;
			presentInfoKhr.pSwapchains = &info.ptrSwapChain->swapChain;
			presentInfoKhr.pImageIndices = &info.imageIndex;
			VkResult result = vkQueuePresentKHR(this->queue, &presentInfoKhr);
			Coders::vulkanProcessingError(result);
		}

		void Queue::wait()
		{
			vkQueueWaitIdle(this->queue);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
