#include "vk_graphicsQueue.hpp"
//
// Created by kisly on 11.09.2025.
//

#include "vk_graphicsQueue.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "vk_semaphore.hpp"
#include "vk_commandBuffer.hpp"
#include "vk_swapChain.hpp"
#include "vk_fence.hpp"
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

		void Queue::submit(const QueueSubmitInfo& qs) const
		{
			VkSubmitInfo submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
			submitInfo.waitSemaphoreCount = (qs.ptrWaitSemaphore != nullptr) ? 1 : 0;
			submitInfo.pWaitSemaphores = {
					(qs.ptrWaitSemaphore != nullptr) ? qs.ptrWaitSemaphore->getVkPtrSemaphore() : nullptr
			};
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = qs.PtrCommandBuffer->getVkPtrCommandBuffer();

			submitInfo.signalSemaphoreCount = (qs.ptrFinishSignalSemaphore != nullptr) ? 1 : 0;
			submitInfo.pSignalSemaphores = {
					(qs.ptrFinishSignalSemaphore != nullptr) ? qs.ptrFinishSignalSemaphore->getVkPtrSemaphore() : nullptr
			};

			VkResult result = vkQueueSubmit(
					this->queue,
					1,
					&submitInfo,
					(qs.ptrFence == nullptr) ? VK_NULL_HANDLE : qs.ptrFence->getVkFence());
			coders::vulkanProcessingError(result);
		}

		void Queue::submits(const QueueSubmitsInfo& qs)
		{
			VkSubmitInfo submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount = qs.countWaitSemaphores;
			submitInfo.signalSemaphoreCount = qs.countFinishSignalSemaphores;
			submitInfo.commandBufferCount = qs.countCommandBuffers;

			std::vector<VkCommandBuffer> vecCommandBuffes = {};
			std::vector<VkPipelineStageFlags> vecWaitStages = {};
			std::vector<VkSemaphore> waitSemaphores = {};
			std::vector<VkSemaphore> finishSemaphores = {};
			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

			vecWaitStages.resize(qs.countWaitSemaphores);
			waitSemaphores.resize(qs.countWaitSemaphores);
			finishSemaphores.resize(qs.countFinishSignalSemaphores);
			vecCommandBuffes.resize(qs.countCommandBuffers);

			for (size_t i = 0; i < vecWaitStages.size(); i++)
			{
				waitSemaphores[i] = qs.ptrWaitSemaphores[i]->getVkSemaphore();
				vecWaitStages[i] = waitStages[0];
			}

			for (size_t i = 0; i < finishSemaphores.size(); i++)
			{
				finishSemaphores[i] = qs.ptrFinishSignalSemaphores[i]->getVkSemaphore();
			}

			for (size_t i = 0; i < vecCommandBuffes.size(); i++)
			{
				vecCommandBuffes[i] = qs.PtrCommandBuffers[i]->getVkCommandBuffer();
			}
			
			submitInfo.pSignalSemaphores = finishSemaphores.data();
			submitInfo.pWaitSemaphores = waitSemaphores.data();
			submitInfo.pWaitDstStageMask = vecWaitStages.data();
			submitInfo.pCommandBuffers = vecCommandBuffes.data();

			VkResult result = vkQueueSubmit(
					this->queue,
					1,
					&submitInfo,
					(qs.ptrFence == nullptr) ? VK_NULL_HANDLE : qs.ptrFence->getVkFence());
			coders::vulkanProcessingError(result);
		}

		void Queue::present(const QueuePresentInfo& qp) const
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

		void Queue::wait() const
		{
			vkQueueWaitIdle(this->queue);
		}

		VkQueue Queue::getVkQueue() const
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

