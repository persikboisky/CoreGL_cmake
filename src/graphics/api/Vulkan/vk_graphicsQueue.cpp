//
// Created by kisly on 11.09.2025.
//

#include "vk_graphicsQueue.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "vk_semaphore.hpp"
#include "vk_commandBuffer.hpp"
#include "vk_swapChain.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		Queue::Queue(Device& device, uint32_t queueIndex)
		{
			vkGetDeviceQueue(
				device.getDevice(),
				device.getGraphicsQueueFamilyIndex(),
				queueIndex,
				&this->queue);
		}

		Queue Queue::get(class Device& device, uint32_t queueIndex)
		{
			return Queue(device, queueIndex);
		}

		Queue Queue::ptrGet(Device& device, uint32_t queueIndex)
		{
			return Queue(device, queueIndex);
		}

		void Queue::submit(const queueSubmitInfo& qs)
		{
			VkSubmitInfo submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
			submitInfo.waitSemaphoreCount = 1;
			submitInfo.pWaitSemaphores = qs.ptrWaitPtrSemaphore->getVkPtrSemaphore();
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = qs.PtrCommandBuffer->getVkPtrCommandBuffer();

			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = qs.ptrFinishSignalSemaphore->getVkPtrSemaphore();

			VkResult result = vkQueueSubmit(this->queue, 1, &submitInfo, VK_NULL_HANDLE);
			coders::vulkanProcessingError(result);
		}

		void Queue::present(const queuePresentInfo& qp)
		{
			VkPresentInfoKHR presentInfo = {};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount = 1;
			presentInfo.pWaitSemaphores = qp.ptrWaitPtrSemaphore->getVkPtrSemaphore();

			VkSwapchainKHR swapChains[] = {qp.ptrSwapChain->getVkSwapchainKHR() };
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = swapChains;
			presentInfo.pImageIndices = &qp.imageIndex;
			presentInfo.pResults = nullptr;
			presentInfo.pNext = nullptr;

			vkQueuePresentKHR(this->queue, &presentInfo);
		}

		void Queue::wait()
		{
			vkQueueWaitIdle(this->queue);
		}

		VkQueue Queue::getVkQueue()
		{
			return this->queue;
		}

		VkQueue* Queue::getVkPtrQueue()
		{
			return &this->queue;
		}
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)

