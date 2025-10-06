//
// Created by kisly on 14.09.2025.
//

#include "vk_vertexBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "../../../util/coders.hpp"
#include "../../../util/types.hpp"
#include <iostream>

namespace core
{
	namespace vulkan
	{
		VertexBuffer::VertexBuffer(VertexBufferInfo& info) : ptrDevice(info.ptrDevice->getPtrDevice()), binding(info.binding)
		{
			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.pNext = nullptr;
			bufferInfo.size = sizeof(info.arrayVertices[0]) * info.lengthArray;
			bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			this->sizeOfBytes = bufferInfo.size;
			this->nByteToOneElement = sizeof(info.arrayVertices[0]);

			VkResult result = vkCreateBuffer(
					info.ptrDevice->getDevice(),
					&bufferInfo,
					nullptr,
					&this->buffer);
			coders::vulkanProcessingError(result);

			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(info.ptrDevice->getDevice(), buffer, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = info.ptrDevice->findMemoryType(
					memRequirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			result = vkAllocateMemory(
					info.ptrDevice->getDevice(),
					&allocInfo,
					nullptr,
					&this->bufferMemory);
			coders::vulkanProcessingError(result);

			result = vkBindBufferMemory(
					info.ptrDevice->getDevice(),
					buffer,
					this->bufferMemory,
					0);
			coders::vulkanProcessingError(result);

			void* pData;
			vkMapMemory(
					info.ptrDevice->getDevice(),
					this->bufferMemory,
					0,
					memRequirements.size,
					0,
					&pData);
			memcpy(
					pData,
					info.arrayVertices,
					static_cast<size_t>(memRequirements.size));
			vkUnmapMemory(
					info.ptrDevice->getDevice(),
					this->bufferMemory);

			this->bindingDescription.binding = info.binding;
			this->bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			this->bindingDescription.stride = info.countElementForVertex * this->nByteToOneElement;
		}

		VertexBuffer VertexBuffer::create(VertexBufferInfo& info)
		{
			return VertexBuffer(info);
		}

		VertexBuffer* VertexBuffer::ptrCreate(VertexBufferInfo& info)
		{
			return new VertexBuffer(info);
		}

		VertexBuffer::~VertexBuffer()
		{
			vkFreeMemory(*this->ptrDevice, this->bufferMemory, nullptr);
			vkDestroyBuffer(*this->ptrDevice, this->buffer, nullptr);
		}

		uint64_t VertexBuffer::getSizeOfBytes() const
		{
			return this->sizeOfBytes;
		}

		void VertexBuffer::addAttribute(uint32_t location, const FORMAT_VARIABLE& format, uint32_t offset)
		{
			VkVertexInputAttributeDescription inputAttributeDescription = {};
			inputAttributeDescription.binding = this->binding;
			inputAttributeDescription.format = vulkan::convertFormat(format);
			inputAttributeDescription.location = location;
			inputAttributeDescription.offset = offset * this->nByteToOneElement;
			this->attributeDescriptions.push_back(inputAttributeDescription);
		}

		VkVertexInputBindingDescription VertexBuffer::getVkVertexInputBindingDescription()
		{
			return this->bindingDescription;
		}

		std::vector<VkVertexInputAttributeDescription> VertexBuffer::getVkVertexInputAttributeDescriptions()
		{
			return this->attributeDescriptions;
		}

		VkBuffer VertexBuffer::getVkBuffer()
		{
			return this->buffer;
		}

		VkBuffer* VertexBuffer::getPtrVkBuffer()
		{
			return &this->buffer;
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

