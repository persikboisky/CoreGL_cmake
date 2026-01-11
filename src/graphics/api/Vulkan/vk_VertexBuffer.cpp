//
// Created by kisly on 23.12.2025.
//

#include "vk_VertexBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "core/vk_Buffer.hpp"
#include "core/vk_CommandBuffer.hpp"
#include "core/vk_CommandPool.hpp"
#include "core/vk_Device.hpp"
#include "core/vk_PhysicalDevices.hpp"
#include "core/vk_Queue.hpp"

namespace core::vulkan
{
    VertexBuffer::VertexBuffer(const VertexBufferCreateInfo& info)
    {
        BufferCreateInfo bufferCreateInfo = {};
        bufferCreateInfo.data = info.data;
        bufferCreateInfo.size = info.size;
        bufferCreateInfo.exclusiveMode = true;
        bufferCreateInfo.ptrDevice = info.ptrDevice;
        bufferCreateInfo.queueFamilyIndices = {};
        bufferCreateInfo.typeBuffer = TYPE_USAGE_BUFFER::TRANSFER_SRC;
        bufferCreateInfo.typeMemory = TYPE_MEMORY::HOST;
        Buffer buffer = Buffer::create(bufferCreateInfo);

        bufferCreateInfo.typeBuffer = TYPE_USAGE_BUFFER::VERTEX_TRANSFER_DST;
        bufferCreateInfo.typeMemory = TYPE_MEMORY::DEVICE_LOCAL;
        ptrBuffer = Buffer::ptrCreate(bufferCreateInfo);

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

    VertexBuffer::~VertexBuffer()
    {
        delete ptrBuffer;
    }

    VertexBuffer VertexBuffer::create(const VertexBufferCreateInfo &info)
    {
        return VertexBuffer(info);
    }

    VertexBuffer *VertexBuffer::ptrCreate(const VertexBufferCreateInfo &info)
    {
        return new VertexBuffer(info);
    }

} // namespace core::vulkan

#endif // defined(CORE_INCLUDE_VULKAN)
