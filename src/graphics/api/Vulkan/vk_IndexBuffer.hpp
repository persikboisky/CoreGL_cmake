//
// Created by kisly on 23.12.2025.
//

#ifndef VK_INDEXBUFFER_HPP
#define VK_INDEXBUFFER_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)

typedef unsigned long long uint64_t;

namespace core::vulkan
{
    class Buffer;
    class Device;

    struct IndexBufferCreateInfo
    {
        Device* ptrDevice = nullptr;
        void* data = nullptr;
        uint64_t size = 0;
    };

    class IndexBuffer
    {
    protected:
        friend class CommandBuffer;

    private:
        Buffer* ptrBuffer = nullptr;

        IndexBuffer(const IndexBufferCreateInfo& info);

    public:
        ~IndexBuffer();

        static IndexBuffer create(const IndexBufferCreateInfo& info);
        static IndexBuffer* ptrCreate(const IndexBufferCreateInfo& info);
    };
} // namespace core

#endif // defined(CORE_INCLUDE_VULKAN)
#endif // VK_INDEXBUFFER_HPP
