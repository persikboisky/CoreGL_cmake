//
// Created by kisly on 23.12.2025.
//

#include "vk_IndexBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "core/vk_Buffer.hpp"
#include "core/vk_CommandBuffer.hpp"
#include "core/vk_CommandPool.hpp"
#include "core/vk_Device.hpp"
#include "core/vk_PhysicalDevices.hpp"
#include "core/vk_Queue.hpp"

namespace core::vulkan
{
    IndexBuffer::IndexBuffer(const IndexBufferCreateInfo &info)
    {
        BufferCreateInfo bufferCI = {};
        bufferCI.size = info.size;
        bufferCI.data = info.data;
        bufferCI.ptrDevice = info.ptrDevice;
        bufferCI.exclusiveMode = true;
        bufferCI.queueFamilyIndices = {};
        bufferCI.typeBuffer = TYPE_USAGE_BUFFER::TRANSFER_SRC;
        bufferCI.typeMemory = TYPE_MEMORY::HOST;
        Buffer buffer = Buffer::create(bufferCI);

        bufferCI.typeBuffer = TYPE_USAGE_BUFFER::INDEX_TRANSFER_DST;
        bufferCI.typeMemory = TYPE_MEMORY::DEVICE_LOCAL;
        ptrBuffer = Buffer::ptrCreate(bufferCI);

        CommandPoolCreateInfo commandPoolInfo = {};
        commandPoolInfo.ptrDevice = info.ptrDevice;
        commandPoolInfo.flagAllowResetBuffer = false;
        commandPoolInfo.queueFamilyIndex =
            PhysicalDeviceInfo(info.ptrDevice->physicalDevice).getQueueFamilyIndex(OPERATES_TYPE::TRANSFER);
        CommandPool commandPool = CommandPool::create(commandPoolInfo);
        CommandBuffer commandBuffer = CommandBuffer::create(commandPool);

        commandBuffer.begin();
        commandBuffer.copyBuffer(&buffer, ptrBuffer, info.size);
        commandBuffer.end();

        SubmitInfo submitInfo = {};
        submitInfo.vecPtrCommandBuffer = {&commandBuffer};

        Queue queue = Queue::get(*info.ptrDevice, commandPoolInfo.queueFamilyIndex, 0);
        queue.submit(submitInfo);
        queue.wait();
    }

    IndexBuffer::~IndexBuffer()
    {
        delete ptrBuffer;
    }

    IndexBuffer IndexBuffer::create(const IndexBufferCreateInfo &info)
    {
        return IndexBuffer(info);
    }

    IndexBuffer *IndexBuffer::ptrCreate(const IndexBufferCreateInfo &info)
    {
        return new IndexBuffer(info);
    }

} // namespace core

#endif //defined(CORE_INCLUDE_VULKAN)