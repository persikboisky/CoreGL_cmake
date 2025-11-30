//
// Created by kisly on 11.09.2025.
//

#include <iostream>
#include "vk_VertexBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Device.hpp"
#include "vk_Queue.hpp"
#include "vk_CommandPool.hpp"
#include "vk_CommandBuffer.hpp"
#include "vk_Buffer.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		VertexBuffer::VertexBuffer(const VertexBufferInfo& info)
		{
			BufferCreateInfo bufferCreateInfo = {};
			bufferCreateInfo.ptrDevice = info.ptrDevice;
			bufferCreateInfo.typeBuffer = TYPE_USAGE_BUFFER::TRANSFER_SRC;
			bufferCreateInfo.exclusiveMode = true;
			bufferCreateInfo.typeMemory = TYPE_MEMORY::HOST;
			bufferCreateInfo.data = info.data;
			bufferCreateInfo.size = info.size;
			Buffer* ptrStagingBuffer = Buffer::ptrCreate(bufferCreateInfo);

			bufferCreateInfo.typeBuffer = TYPE_USAGE_BUFFER::VERTEX_TRANSFER_DST;
			bufferCreateInfo.typeMemory = TYPE_MEMORY::DEVICE_LOCAL;
			this->buffer = Buffer::ptrCreate(bufferCreateInfo);

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

			cmd->copyBuffer(ptrStagingBuffer, this->buffer, info.size);

			SubmitInfo submitInfo = {};
			submitInfo.ptrCommandBuffer = cmd;
			cmd->end();
			queue->submit(submitInfo);
			queue->wait();

			delete cmd;
			delete pool;
			delete queue;
			delete ptrStagingBuffer;
		}

		VertexBuffer::~VertexBuffer()
		{
			delete buffer;
		}

		VertexBuffer VertexBuffer::create(const VertexBufferInfo& info)
		{
			return VertexBuffer(info);
		}

		VertexBuffer* VertexBuffer::ptrCreate(const VertexBufferInfo& info)
		{
			return new VertexBuffer(info);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
