//
// Created by kisly on 09.09.2025.
//

#include "vk_Queue.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/Coders.hpp"
#include "vk_CommandBuffer.hpp"
#include "vk_Device.hpp"
#include "vk_SwapChain.hpp"
#include "vk_Sync.hpp"

namespace core
{
	namespace vulkan
	{
		Queue::Queue(class Device &device, uint32_t queueFamilyIndex, uint32_t queueIndex)
		{
		    vkGetDeviceQueue(device.device, queueFamilyIndex, queueIndex, &queue);
		}

        Queue Queue::get(class Device &device, uint32_t queueFamilyIndex, uint32_t queueIndex)
        {
            return Queue(device, queueFamilyIndex, queueIndex);
        }

        Queue *Queue::ptrGet(class Device &device, uint32_t queueFamilyIndex, uint32_t queueIndex)
        {
		    return new Queue(device, queueFamilyIndex, queueIndex);
        }

		void Queue::submit(SubmitInfo& info)
		{
            const auto cmds = new VkCommandBuffer[info.ptrCommandBuffer.size()];
            for (size_t i = 0; i < info.ptrCommandBuffer.size(); i++)
                cmds[i] = info.ptrCommandBuffer[i]->commandBuffer;

            const auto waitSemaphores = new VkSemaphore[info.ptrWaitSemaphore.size()];
		    for (size_t i = 0; i < info.ptrWaitSemaphore.size(); i++)
		        waitSemaphores[i] = info.ptrWaitSemaphore[i]->semaphore;

            const auto signalSemaphores = new VkSemaphore[info.ptrSignalSemaphore.size()];
		    for (size_t i = 0; i < info.ptrSignalSemaphore.size(); i++)
		        signalSemaphores[i] = info.ptrSignalSemaphore[i]->semaphore;

			VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
			VkSubmitInfo submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.pNext = nullptr;
			submitInfo.pCommandBuffers = cmds;
			submitInfo.commandBufferCount = info.ptrCommandBuffer.size();
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.pSignalSemaphores = signalSemaphores;
			submitInfo.signalSemaphoreCount = info.ptrSignalSemaphore.size();
			submitInfo.pWaitSemaphores = waitSemaphores;
			submitInfo.waitSemaphoreCount = info.ptrWaitSemaphore.size();

			vkQueueSubmit(this->queue, 1, &submitInfo,
			    info.ptrFence != nullptr ? info.ptrFence->fence : VK_NULL_HANDLE);

		    delete [] cmds;
		    delete [] waitSemaphores;
		    delete [] signalSemaphores;
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
