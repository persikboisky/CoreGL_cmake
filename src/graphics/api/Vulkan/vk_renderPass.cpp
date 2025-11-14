//
// Created by kisly on 05.09.2025.
//

#include "vk_RenderPass.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Device.hpp"
#include "vk_Attachments.hpp"

namespace core
{
	namespace vulkan
	{
		static inline VkAttachmentLoadOp convertAttachmentLoadOp(const LoadOp& loadOp)
		{
			return (loadOp == LoadOp::LOAD_OP_LOAD) ? VK_ATTACHMENT_LOAD_OP_LOAD : VK_ATTACHMENT_LOAD_OP_CLEAR;
		}

		static inline VkImageLayout convertInitLayout(const InitialLayout& initialLayout)
		{
			switch (initialLayout)
			{
			case InitialLayout::LAYOUT_UNDEFINED:
				return VK_IMAGE_LAYOUT_UNDEFINED;
			case InitialLayout::LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
				return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			case InitialLayout::LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
				return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			case InitialLayout::LAYOUT_SHADER_READ_ONLY_OPTIMAL:
				return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			}
		}

		static inline VkImageLayout convertFinalLayout(const FinalLayout& finalLayout)
		{
			switch (finalLayout)
			{
			case FinalLayout::LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
				return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			case FinalLayout::LAYOUT_SHADER_READ_ONLY_OPTIMAL:
				return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			case FinalLayout::LAYOUT_PRESENT_SRC_KHR:
				return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			case FinalLayout::LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
				return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			}
		}

		RenderPass::RenderPass(const RenderPassInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			std::vector<VkAttachmentDescription> attachmentDescription = {};
			std::vector<VkAttachmentReference> attachmentReference = {};

			attachmentDescription.resize(info.ptrArrayAttachmentsInfo.size());
			attachmentReference.resize(info.ptrArrayAttachmentsInfo.size());

			unsigned int index = 0;
			for (AttachmentsInfo* a : info.ptrArrayAttachmentsInfo)
			{
				attachmentDescription[index].loadOp = convertAttachmentLoadOp(a->loadOp);
				attachmentDescription[index].flags = 0;
				attachmentDescription[index].samples = VK_SAMPLE_COUNT_1_BIT;
				attachmentDescription[index].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
				attachmentDescription[index].initialLayout = convertInitLayout(a->initLayout);
				attachmentDescription[index].finalLayout = convertFinalLayout(a->finalLayout);
				attachmentDescription[index].stencilLoadOp = attachmentDescription[index].loadOp;
				attachmentDescription[index].stencilStoreOp = attachmentDescription[index].storeOp;

				switch (a->format)
				{
				case FormatAttachment::COLOR:
					attachmentDescription[index].format = info.ptrDevice->surfaceFormat.format;
					break;
				case FormatAttachment::DEPTH:
					attachmentDescription[index].format = VK_FORMAT_D32_SFLOAT;
					break;
				default:
					attachmentDescription[index].format = VK_FORMAT_D32_SFLOAT_S8_UINT;
					break;
				}

				attachmentReference[index].attachment = index;
//				attachmentReference[index].layout =

				index++;
			}

			VkSubpassDescription subpass = {};
//			subpass.
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

