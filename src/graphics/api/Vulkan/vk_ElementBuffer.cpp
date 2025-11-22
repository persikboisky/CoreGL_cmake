//
// Created by kisly on 21.11.2025.
//

#include "vk_ElementBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Device.hpp"
#include "vk_Queue.hpp"
#include "vk_CommandPool.hpp"
#include "vk_CommandBuffer.hpp"
#include "../../../util/coders.hpp"
#include <cstring>

namespace core
{
	namespace vulkan
	{
		ElementBuffer::ElementBuffer(const ElementBufferInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			VkBuffer stagingBuffer;
			VkDeviceMemory stagingBufferMemory;

			VkBufferCreateInfo bufferInfo{};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = info.size;
			bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			VkResult result = vkCreateBuffer(
					info.ptrDevice->device,
					&bufferInfo,
					nullptr,
					&stagingBuffer);
			coders::vulkanProcessingError(result);

			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(
					info.ptrDevice->device,
					stagingBuffer,
					&memRequirements);

			VkMemoryAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = info.ptrDevice->findMemoryType(
					memRequirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			result = vkAllocateMemory(
					info.ptrDevice->device,
					&allocInfo,
					nullptr,
					&stagingBufferMemory);
			coders::vulkanProcessingError(result);
			vkBindBufferMemory(info.ptrDevice->device, stagingBuffer, stagingBufferMemory, 0);

			void *data;
			vkMapMemory(info.ptrDevice->device, stagingBufferMemory, 0, info.size, 0, &data);
			memcpy(data, info.data, info.size);
			vkUnmapMemory(info.ptrDevice->device, stagingBufferMemory);

			bufferInfo.usage =  VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			result = vkCreateBuffer(
					info.ptrDevice->device,
					&bufferInfo,
					nullptr,
					&this->buffer);
			coders::vulkanProcessingError(result);

			vkGetBufferMemoryRequirements(
					info.ptrDevice->device,
					this->buffer,
					&memRequirements);

			allocInfo.memoryTypeIndex = info.ptrDevice->findMemoryType(
					memRequirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
			result = vkAllocateMemory(
					info.ptrDevice->device,
					&allocInfo,
					nullptr,
					&this->memory);
			coders::vulkanProcessingError(result);
			vkBindBufferMemory(info.ptrDevice->device, this->buffer, this->memory, 0);

			Queue *queue = Queue::ptrCreate(*info.ptrDevice, TypeFamilyQueue::GRAPHICS);

			CommandPoolInfo commandPoolInfo = {};
			commandPoolInfo.ptrDevice = info.ptrDevice;
			commandPoolInfo.queueFamilyIndex = info.ptrDevice->getQueueFamilyIndex(TypeFamilyQueue::GRAPHICS);
			commandPoolInfo.flagAllowResetBuffer = false;
			CommandPool *pool = CommandPool::ptrCreate(commandPoolInfo);
			CommandBuffer *cmd = CommandBuffer::ptrCreate(*info.ptrDevice, *pool);

			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			vkBeginCommandBuffer(cmd->commandBuffer, &beginInfo);

			VkBufferCopy copyRegion{};
			copyRegion.srcOffset = 0;
			copyRegion.dstOffset = 0;
			copyRegion.size = info.size;
			vkCmdCopyBuffer(
					cmd->commandBuffer,
					stagingBuffer,
					this->buffer,
					1,
					&copyRegion);

			SubmitInfo submitInfo = {};
			submitInfo.ptrCommandBuffer = cmd;
			cmd->end();
			queue->submit(submitInfo);
			queue->wait();

			delete cmd;
			delete pool;
			delete queue;

			vkDestroyBuffer(info.ptrDevice->device, stagingBuffer, nullptr);
			vkFreeMemory(info.ptrDevice->device, stagingBufferMemory, nullptr);
		}

		ElementBuffer::~ElementBuffer()
		{
			vkDestroyBuffer(*this->ptrDevice, this->buffer, nullptr);
			vkFreeMemory(*this->ptrDevice, this->memory, nullptr);
		}

		ElementBuffer ElementBuffer::create(const ElementBufferInfo& info)
		{
			return ElementBuffer(info);
		}

		ElementBuffer* ElementBuffer::ptrCreate(const ElementBufferInfo& info)
		{
			return new ElementBuffer(info);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
