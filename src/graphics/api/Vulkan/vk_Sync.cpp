//
// Created by kisly on 09.09.2025.
//

#include "vk_Sync.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/Coders.hpp"
#include "vk_Device.hpp"

namespace core::vulkan
{
	Semaphore::Semaphore(const Device& device) : device(device.device)
	{
		VkSemaphoreCreateInfo semaphoreCreateInfo = {};
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		semaphoreCreateInfo.pNext = nullptr;
		semaphoreCreateInfo.flags = 0;

	    const VkResult result = vkCreateSemaphore(
	        device.device,
	        &semaphoreCreateInfo,
			nullptr,
			&this->semaphore);
	    Coders::vulkanProcessingError(result);
	}

	Semaphore::~Semaphore()
	{
		vkDestroySemaphore(this->device, this->semaphore, nullptr);
	}

	Semaphore Semaphore::create(const Device& device)
	{
		return Semaphore(device);
	}

	Semaphore *Semaphore::ptrCreate(const Device& device)
	{
		return new Semaphore(device);
	}

    Fence::Fence(const Device &device, bool signaled) : device(device.device)
    {
	    VkFenceCreateInfo fenceInfo = {};
	    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	    fenceInfo.flags = signaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0;
	    const VkResult result = vkCreateFence(device.device, &fenceInfo, nullptr, &fence);
	    Coders::vulkanProcessingError(result);
    }

    Fence::~Fence()
    {
	    vkDestroyFence(device, fence, nullptr);
    }

    Fence Fence::create(const class Device &device, bool signaled)
    {
	    return Fence(device, signaled);
    }

    Fence *Fence::ptrCreate(const class Device &device, bool signaled)
    {
	    return new Fence(device, signaled);
    }

    void Fence::reset() const
    {
	    vkResetFences(device, 1, &fence);
    }

    void Fence::wait(bool flagWait, uint64_t timeout) const
    {
	    vkWaitForFences(device, 1, &fence, flagWait ? VK_TRUE : VK_FALSE, timeout);
    }

} // vulkan::corre

#endif //defined(CORE_INCLUDE_VULKAN)

