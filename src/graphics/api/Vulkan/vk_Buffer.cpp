//
// Created by kisly on 22.11.2025.
//

#include "vk_Buffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/Coders.hpp"
#include "vk_Device.hpp"

namespace core
{
	namespace vulkan
	{
		static inline VkBufferUsageFlags convertBufferType(const TYPE_USAGE_BUFFER& type)
		{
			switch (type)
			{
			case TYPE_USAGE_BUFFER::INDEX:
				return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
			case TYPE_USAGE_BUFFER::STORAGE:
				return VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
			case TYPE_USAGE_BUFFER::TRANSFER_DST:
				return VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case TYPE_USAGE_BUFFER::TRANSFER_SRC:
				return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
			case TYPE_USAGE_BUFFER::UNIFORM:
				return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
			case TYPE_USAGE_BUFFER::INDIRECT:
				return VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
			case TYPE_USAGE_BUFFER::INDEX_TRANSFER_DST:
				return VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case TYPE_USAGE_BUFFER::VERTEX_TRANSFER_DST:
				return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			default:
				return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
			}
		}

		Buffer::Buffer(const BufferCreateInfo& info) : ptrDevice(&info.ptrDevice->device), size(info.size)
		{
			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = info.size;
			bufferInfo.flags = 0;
			bufferInfo.usage = convertBufferType(info.typeBuffer);
			bufferInfo.sharingMode = info.exclusiveMode ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT;
			bufferInfo.pNext = nullptr;
			bufferInfo.pQueueFamilyIndices = nullptr;
			bufferInfo.queueFamilyIndexCount = 0;
			VkResult result = vkCreateBuffer(
					info.ptrDevice->device,
					&bufferInfo,
					nullptr,
					&this->buffer);
			Coders::vulkanProcessingError(result);

			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(
					info.ptrDevice->device,
					this->buffer,
					&memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = info.ptrDevice->findMemoryType(
					memRequirements.memoryTypeBits,
					(info.typeMemory == TYPE_MEMORY::HOST) ?
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT :
					VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
			result = vkAllocateMemory(
					info.ptrDevice->device,
					&allocInfo,
					nullptr,
					&this->memory);
			Coders::vulkanProcessingError(result);
			vkBindBufferMemory(info.ptrDevice->device, this->buffer, this->memory, 0);

			if (info.typeMemory != TYPE_MEMORY::DEVICE_LOCAL && info.data != nullptr)
			{
				this->copy(info.data, info.size);
			}
		}

		Buffer Buffer::create(const BufferCreateInfo& info)
		{
			return Buffer(info);
		}

		Buffer* Buffer::ptrCreate(const BufferCreateInfo& info)
		{
			return new Buffer(info);
		}

		Buffer::~Buffer()
		{
			vkFreeMemory(*this->ptrDevice, this->memory, nullptr);
			vkDestroyBuffer(*this->ptrDevice, this->buffer, nullptr);
		}

		void Buffer::copy(void* data, uint64_t size)
		{
			void* ptrMemory;
			vkMapMemory(*this->ptrDevice, this->memory, 0, size, 0, &ptrMemory);
			memcpy(ptrMemory, data, size);
			vkUnmapMemory(*this->ptrDevice, this->memory);
		}

		uint64_t Buffer::getSzie() const
		{
			return this->size;
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
