//
// Created by kisly on 05.09.2025.
//

#include "vk_RenderPass.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../../util/Coders.hpp"
#include "../../../../types/apiTypes.hpp"
#include "vk_Device.hpp"

namespace core
{
	namespace vulkan
	{
		RenderPass::RenderPass(const RenderPassCreateInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
            std::vector<VkAttachmentDescription> attachmentDescriptions(info.attachments.size());
		    std::vector<VkSubpassDependency> subpassDependencies(info.dependencies.size());
		    std::vector<VkSubpassDescription> subpassDescriptions(info.subpasses.size());

		    auto* pDepthStencilAttachments = new VkAttachmentReference[info.subpasses.size()];
		    auto* pResolveAttachments = new VkAttachmentReference[info.subpasses.size()];

		    std::vector<std::vector<VkAttachmentReference>> pInputAttachments(info.subpasses.size());
		    std::vector<std::vector<VkAttachmentReference>> pColorAttachments(info.subpasses.size());

		    uint32_t index = 0;
		    for (const auto& attachment : info.attachments)
		    {
		        attachmentDescriptions[index].finalLayout = Convert::convert(attachment.finalLayout);
		        attachmentDescriptions[index].format = Convert::convert(attachment.format);
		        attachmentDescriptions[index].initialLayout = Convert::convert(attachment.initialLayout);
		        attachmentDescriptions[index].stencilLoadOp = Convert::convert(attachment.StencilLoadOp);
		        attachmentDescriptions[index].stencilStoreOp = Convert::convert(attachment.StencilStoreOp);
		        attachmentDescriptions[index].samples = Convert::convert(attachment.Samples);
		        attachmentDescriptions[index].loadOp = Convert::convert(attachment.LoadOp);
		        attachmentDescriptions[index].storeOp = Convert::convert(attachment.StoreOp);
                index++;
		    }

		    index = 0;
		    for (const auto& dependency : info.dependencies)
		    {
		        subpassDependencies[index].dstSubpass = dependency.dstSubpass;
		        subpassDependencies[index].srcSubpass = dependency.srcSubpass;
		        subpassDependencies[index].srcAccessMask = Convert::convert(dependency.srcAccess);
		        subpassDependencies[index].dstAccessMask = Convert::convert(dependency.dstAccess);
		        subpassDependencies[index].dstStageMask = Convert::convert(dependency.dstStage);
		        subpassDependencies[index].srcStageMask = Convert::convert(dependency.srcStage);
		    }

		    index = 0;
		    for (const auto& subpass : info.subpasses)
		    {
		        pColorAttachments[index].resize(subpass.colorAttachmentReferences.size());
                for (uint32_t i = 0; i < subpass.colorAttachmentReferences.size(); i++)
                {
                    pColorAttachments[index][i].attachment = subpass.colorAttachmentReferences[i].attachment;
                    pColorAttachments[index][i].layout = Convert::convert(subpass.colorAttachmentReferences[i].layout);
                }

		        pInputAttachments[index].resize(subpass.inputAttachmentReferences.size());
		        for (uint32_t i = 0; i < subpass.inputAttachmentReferences.size(); i++)
		        {
		            pInputAttachments[index][i].attachment = subpass.inputAttachmentReferences[i].attachment;
		            pInputAttachments[index][i].layout = Convert::convert(subpass.inputAttachmentReferences[i].layout);
		        }

		        subpassDescriptions[index].inputAttachmentCount = subpass.inputAttachmentReferences.size();
		        subpassDescriptions[index].preserveAttachmentCount = subpass.preserveAttachments.size();
		        subpassDescriptions[index].colorAttachmentCount = subpass.colorAttachmentReferences.size();
		        subpassDescriptions[index].pInputAttachments = pInputAttachments[index].data();
		        subpassDescriptions[index].pColorAttachments = pColorAttachments[index].data();
		        subpassDescriptions[index].pPreserveAttachments = subpass.preserveAttachments.data();
		        subpassDescriptions[index].pipelineBindPoint = Convert::convert(subpass.bindPoint);

		        if (subpass.ptrResolveAttachmentReferences == nullptr)
		            subpassDescriptions[index].pResolveAttachments = nullptr;
		        else
		        {
                    pResolveAttachments[index].attachment = subpass.ptrResolveAttachmentReferences->attachment;
		            pResolveAttachments[index].layout = Convert::convert(subpass.ptrResolveAttachmentReferences->layout);
		            subpassDescriptions[index].pResolveAttachments = &pResolveAttachments[index];
		        }

		        if (subpass.ptrDepthStencilAttachmentReferences == nullptr)
		            subpassDescriptions[index].pDepthStencilAttachment = nullptr;
		        else
		        {
		            pDepthStencilAttachments[index].attachment = subpass.ptrDepthStencilAttachmentReferences->attachment;
		            pDepthStencilAttachments[index].layout = Convert::convert(subpass.ptrDepthStencilAttachmentReferences->layout);
		            subpassDescriptions[index].pDepthStencilAttachment = &pDepthStencilAttachments[index];
		        }
		    }

		    VkRenderPassCreateInfo createInfo = {};
		    createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		    createInfo.flags = 0;
		    createInfo.pNext = nullptr;
		    createInfo.attachmentCount = static_cast<uint32_t>(attachmentDescriptions.size());
		    createInfo.dependencyCount = static_cast<uint32_t>(subpassDependencies.size());
		    createInfo.subpassCount = static_cast<uint32_t>(subpassDescriptions.size());
		    createInfo.pAttachments = attachmentDescriptions.data();
		    createInfo.pDependencies = subpassDependencies.data();
		    createInfo.pSubpasses = subpassDescriptions.data();

            const VkResult result = vkCreateRenderPass(*this->ptrDevice, &createInfo, nullptr, &this->renderPass);
		    Coders::vulkanProcessingError(result);

		    delete[] pResolveAttachments;
		    delete[] pDepthStencilAttachments;
		}

		RenderPass RenderPass::create(const RenderPassCreateInfo& info)
		{
			return RenderPass(info);
		}

		RenderPass* RenderPass::ptrCreate(const RenderPassCreateInfo& info)
		{
			return new RenderPass(info);
		}

		RenderPass::~RenderPass()
		{
			vkDestroyRenderPass(*this->ptrDevice, this->renderPass, nullptr);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

