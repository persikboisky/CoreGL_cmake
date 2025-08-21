//
// Created by kisly on 21.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vRenderPass.hpp"
#include "vResource.hpp"
#include "vGraphicsPipeline.hpp"
#include <vulkan/vulkan.h>
#include <array>

namespace core
{
    namespace vulkan
    {
        void renderPass::create(piplineContainer *rCnt, apiContainer& cnt)
        {
            rCnt->ptrApiContainer = &cnt;

            VkAttachmentDescription colorAttachment = {};
            colorAttachment.format = cnt.swapChainFormat.format;
            colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
            colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
            colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
            colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

            VkAttachmentReference colorAttachmentRef = {};
            colorAttachmentRef.attachment = 0;
            colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

            VkAttachmentDescription depthAttachment = {};
            depthAttachment.format = findDepthFormat(cnt);
            depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
            depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
            depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

            VkAttachmentReference depthAttachmentRef = {};
            depthAttachmentRef.attachment = 1;
            depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

            VkSubpassDescription subPassDesc = {};
            subPassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
            subPassDesc.colorAttachmentCount = 1;
            subPassDesc.pColorAttachments = &colorAttachmentRef;
            subPassDesc.pDepthStencilAttachment = &depthAttachmentRef;

            VkSubpassDependency dependency = {};
            dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
            dependency.dstSubpass = 0;

            dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            dependency.srcAccessMask = 0;

            dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            dependency.dstStageMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

            const std::array<VkAttachmentDescription, 2> attachments = {
                    colorAttachment, depthAttachment
            };

            VkRenderPassCreateInfo renderPassInfo = {};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
            renderPassInfo.pNext = nullptr;
            renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            renderPassInfo.pAttachments = attachments.data();
            renderPassInfo.subpassCount = 1;
            renderPassInfo.pSubpasses = &subPassDesc;
            renderPassInfo.dependencyCount = 1;
            renderPassInfo.pDependencies = &dependency;

            VkResult result = vkCreateRenderPass(
                    cnt.logicalDevice,
                    &renderPassInfo,
                    nullptr,
                    &rCnt->renderPass);
            coders::vulkanProcessingError(result);
        }

        void renderPass::destroy(piplineContainer *rCnt, const apiContainer& cnt)
        {
            graphicsPipeline::destroy(rCnt, &cnt);
            vkDestroyRenderPass(cnt.logicalDevice, rCnt->renderPass, nullptr);
        }
    } // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)