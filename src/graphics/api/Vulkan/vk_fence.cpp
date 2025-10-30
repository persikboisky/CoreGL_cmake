//
// Created by kisly on 06.10.2025.
//

#include "vk_fence.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		Fence::Fence(Device& device) : ptrDevice(&device.device)
		{
			VkFenceCreateInfo fenceCreateInfo = {};
			fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
			fenceCreateInfo.pNext = nullptr;

			VkResult result = vkCreateFence(
					device.device,
					&fenceCreateInfo,
					nullptr,
					&this->fence);
			coders::vulkanProcessingError(result);
		}

		Fence Fence::create(Device& device)
		{
			return Fence(device);
		}

		Fence* Fence::ptrCreate(Device& device)
		{
			return new Fence(device);
		}

		Fence::~Fence()
		{
			vkDestroyFence(*this->ptrDevice, this->fence, nullptr);
		}

		void Fence::wait(WaitForFencesInfo& info)
		{
			auto ptrFences = new VkFence[info.countFences];
			for (uint32_t i = 0; i < info.countFences; i++)
			{
				ptrFences[i] = info.ptrFences[i]->fence;
			}

			VkResult result = vkWaitForFences(
					info.ptrDevice->device,
					info.countFences,
					ptrFences,
					(info.waitAllFences) ? VK_TRUE : VK_FALSE,
					UINT64_MAX);
			coders::vulkanProcessingError(result);

			delete[] ptrFences;
		}

		void Fence::wait()
		{
			VkResult result = vkWaitForFences(
					*this->ptrDevice,
					1,
					&this->fence,
					VK_TRUE,
					UINT64_MAX);
			coders::vulkanProcessingError(result);
		}

		void Fence::resetFence()
		{
			VkResult result = vkResetFences(
					*this->ptrDevice,
					1,
					&this->fence);
			coders::vulkanProcessingError(result);
		}
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
