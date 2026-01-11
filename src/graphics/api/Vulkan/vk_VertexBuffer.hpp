//
// Created by kisly on 23.12.2025.
//

#ifndef VK_VERTEXBUFFER_HPP
#define VK_VERTEXBUFFER_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)

typedef unsigned long long uint64_t;

namespace core
{
namespace vulkan
{
    class Buffer;
    class Device;

    struct VertexBufferCreateInfo
    {
        Device* ptrDevice = nullptr;
        void* data = nullptr;
        uint64_t size = 0;
    };

    class VertexBuffer
    {
    protected:
        friend class CommandBuffer;

    private:
        Buffer* ptrBuffer = nullptr;

      explicit VertexBuffer(const VertexBufferCreateInfo& info);

    public:
        ~VertexBuffer();

        static VertexBuffer create(const VertexBufferCreateInfo& info);
        static VertexBuffer* ptrCreate(const VertexBufferCreateInfo& info);
    };

} // namespace vulkan
} // namespace core

#endif // defined(CORE_INCLUDE_VULKAN)
#endif // VK_VERTEXBUFFER_HPP
