//
// Created by kisly on 23.11.2025.
//

#include "vk_Descriptor.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/Coders.hpp"
#include "vk_Buffer.hpp"
#include "vk_Device.hpp"
#include "vk_Image.hpp"
#include "vk_ShaderStage.hpp"

namespace core
{
	namespace vulkan
	{
		static inline VkDescriptorType convertDescriptorType(const DESCRIPTOR_TYPE& type)
		{
			return (type == DESCRIPTOR_TYPE::UNIFORM_BUFFER) ?
				   VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER :
				   VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		}

		DescriptorPool::DescriptorPool(const DescriptorPoolCreateInfo& info) : prtDevice(&info.ptrDevice->device)
		{
			auto pPoolSizes = new VkDescriptorPoolSize[info.vecPtrDescriptorPoolSize.size()];
			for (size_t index = 0; index < info.vecPtrDescriptorPoolSize.size(); index++)
			{
				pPoolSizes[index].descriptorCount = info.vecPtrDescriptorPoolSize[index]->count;
				pPoolSizes[index].type = convertDescriptorType(info.vecPtrDescriptorPoolSize[index]->type);
			}

			VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {};
			descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			descriptorPoolCreateInfo.poolSizeCount = static_cast<uint32_t>(info.vecPtrDescriptorPoolSize.size());
			descriptorPoolCreateInfo.pPoolSizes = pPoolSizes;
			descriptorPoolCreateInfo.maxSets = info.maxSets;
			descriptorPoolCreateInfo.pNext = nullptr;
			descriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

			VkResult result = vkCreateDescriptorPool(
					info.ptrDevice->device,
					&descriptorPoolCreateInfo,
					nullptr,
					&this->descriptorPool);
			Coders::vulkanProcessingError(result);

			delete[] pPoolSizes;
		}

		DescriptorPool DescriptorPool::create(const DescriptorPoolCreateInfo& info)
		{
			return DescriptorPool(info);
		}

		DescriptorPool* DescriptorPool::ptrCreate(const DescriptorPoolCreateInfo& info)
		{
			return new DescriptorPool(info);
		}

		DescriptorPool::~DescriptorPool()
		{
			vkDestroyDescriptorPool(*this->prtDevice, this->descriptorPool, nullptr);
		}

		DescriptorSetLayout::DescriptorSetLayout(const DescriptorSetLayoutCreateInfo& info) : prtDevice(&info.ptrDevice->device)
		{
			auto bindings = new VkDescriptorSetLayoutBinding[info.layoutBinding.size()];
			for (size_t index = 0; index < info.layoutBinding.size(); index++)
			{
				bindings[index].binding = info.layoutBinding[index].binding;
				bindings[index].descriptorCount = info.layoutBinding[index].count;
				bindings[index].stageFlags = ShaderModule::convertStage(info.layoutBinding[index].shaderStages);
				bindings[index].descriptorType = convertDescriptorType(info.layoutBinding[index].type);
			}

			VkDescriptorSetLayoutCreateInfo layoutInfo = {};
			layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			layoutInfo.bindingCount = static_cast<uint32_t>(info.layoutBinding.size());
			layoutInfo.pBindings = bindings;
			layoutInfo.flags = 0;
			layoutInfo.pNext = nullptr;

			VkResult result = vkCreateDescriptorSetLayout(
					info.ptrDevice->device,
					&layoutInfo,
					nullptr,
					&this->layout);
			Coders::vulkanProcessingError(result);

			delete[] bindings;
		}

		DescriptorSetLayout::~DescriptorSetLayout()
		{
			vkDestroyDescriptorSetLayout(*this->prtDevice, this->layout, nullptr);
		}

		DescriptorSetLayout DescriptorSetLayout::create(const DescriptorSetLayoutCreateInfo& info)
		{
			return DescriptorSetLayout(info);
		}

		DescriptorSetLayout* DescriptorSetLayout::ptrCreate(const DescriptorSetLayoutCreateInfo& info)
		{
			return new DescriptorSetLayout(info);
		}

		DescriptorSet::DescriptorSet(const DescriptorSetCreateInfo& info) :
			ptrDevice(&info.ptrDevice->device),
			ptrDescriptorPool(&info.ptrDescriptorPool->descriptorPool)
		{
			auto l = new VkDescriptorSetLayout[info.vecPtrLayouts.size()];
			for (size_t i = 0; i < info.vecPtrLayouts.size(); i++)
			{
				l[i] = info.vecPtrLayouts[i]->layout;
			}

			VkDescriptorSetAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			allocInfo.descriptorPool = info.ptrDescriptorPool->descriptorPool;
			allocInfo.descriptorSetCount = static_cast<uint32_t>(info.vecPtrLayouts.size());
			allocInfo.pSetLayouts = l;

			VkResult result = vkAllocateDescriptorSets(
					info.ptrDevice->device,
					&allocInfo,
					&this->descriptorSet);
			Coders::vulkanProcessingError(result);
			delete[] l;
		}

		DescriptorSet::~DescriptorSet()
		{
			vkFreeDescriptorSets(
					*this->ptrDevice,
					*this->ptrDescriptorPool,
					1,
					&this->descriptorSet);
		}

		DescriptorSet DescriptorSet::create(const DescriptorSetCreateInfo& info)
		{
			return DescriptorSet(info);
		}

		DescriptorSet* DescriptorSet::ptrCreate(const DescriptorSetCreateInfo& info)
		{
			return new DescriptorSet(info);
		}

		void DescriptorSet::update(const DescriptorSetUpdateInfo& info)
		{
			if (info.ptrBuffer != nullptr)
			{
				VkDescriptorBufferInfo bufferInfo = {};
				bufferInfo.buffer = info.ptrBuffer->buffer;
				bufferInfo.offset = info.offset;
				bufferInfo.range = info.ptrBuffer->size;

				VkWriteDescriptorSet descriptorWrite = {};
				descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				descriptorWrite.dstSet = this->descriptorSet;
				descriptorWrite.dstBinding = info.binding;
				descriptorWrite.dstArrayElement = 0;
				descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				descriptorWrite.descriptorCount = 1;
				descriptorWrite.pBufferInfo = &bufferInfo;
				vkUpdateDescriptorSets(
						*this->ptrDevice,
						1,
						&descriptorWrite,
						0,
						nullptr
				);
			}
			else
			{
				VkDescriptorImageInfo imageInfo{};
				imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				imageInfo.imageView = info.ptrImageView->imageView;
				imageInfo.sampler = info.ptrSampler->sampler;

				VkWriteDescriptorSet descriptorWrite = {};
				descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				descriptorWrite.dstSet = this->descriptorSet;
				descriptorWrite.dstBinding = info.binding;
				descriptorWrite.dstArrayElement = 0;
				descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				descriptorWrite.descriptorCount = 1;
				descriptorWrite.pBufferInfo = nullptr;
				descriptorWrite.pTexelBufferView = nullptr;
				descriptorWrite.pImageInfo = &imageInfo;

				vkUpdateDescriptorSets(
						*this->ptrDevice,
						1,
						&descriptorWrite,
						0,
						nullptr
				);
			}
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
