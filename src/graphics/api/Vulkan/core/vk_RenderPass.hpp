//
// Created by kisly on 05.09.2025.
//

#ifndef VK_RENDERPASS_HPP_
#define VK_RENDERPASS_HPP_

#include "../../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../../types/apiTypes.hpp"
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
	    struct AttachmentInfo
	    {
	        LOAD_OP LoadOp = LOAD_OP::LOAD_OP_CLEAR;
	        STORE_OP StoreOp = STORE_OP::STORE_OP_STORE;
	        IMAGE_LAYOUT initialLayout = IMAGE_LAYOUT::UNDEFINED;
	        IMAGE_LAYOUT finalLayout = IMAGE_LAYOUT::PRESENT_SRC_KHR;
	        IMAGE_FORMAT format = IMAGE_FORMAT::R8G8B8A8_UNORM;
	        LOAD_OP StencilLoadOp = LOAD_OP::LOAD_OP_DONT_CARE;
	        STORE_OP StencilStoreOp = STORE_OP::STORE_OP_STORE;
	        SAMPLES Samples = SAMPLES::_1BIT;
	    };

	    struct ReferenceInfo
	    {
            uint32_t attachment = 0;
	        IMAGE_LAYOUT layout = IMAGE_LAYOUT::COLOR_ATTACHMENT_OPTIMAL;
	    };

	    struct SubpassInfo
	    {
            std::vector<ReferenceInfo> colorAttachmentReferences = {};
	        std::vector<ReferenceInfo> inputAttachmentReferences = {};
	        std::vector<uint32_t> preserveAttachments = {};
	        ReferenceInfo *ptrDepthStencilAttachmentReferences = nullptr;
	        ReferenceInfo *ptrResolveAttachmentReferences = nullptr;
	        PIPELINE_BIND_POINT bindPoint = PIPELINE_BIND_POINT::GRAPHICS;
	    };

	    struct DependencyInfo
	    {
            uint32_t srcSubpass = 0;
	        uint32_t dstSubpass = 0;
	        PIPELINE_STAGE srcStage = PIPELINE_STAGE::NONE;
	        PIPELINE_STAGE dstStage = PIPELINE_STAGE::NONE;
	        ACCESS srcAccess = ACCESS::NONE;
	        ACCESS dstAccess = ACCESS::NONE;
	    };

		struct RenderPassCreateInfo
		{
			class Device* ptrDevice = nullptr;
		    std::vector<AttachmentInfo> attachments = {};
		    std::vector<SubpassInfo> subpasses = {};
		    std::vector<DependencyInfo> dependencies = {};
		};

		class RenderPass
		{
		protected:
			friend class FrameBuffer;
			friend class CommandBuffer;
			friend class GraphicsPipeline;

		private:
			VkRenderPass renderPass = nullptr;
			VkDevice* ptrDevice = nullptr;

			explicit RenderPass(const RenderPassCreateInfo& info);

		public:
			static RenderPass create(const RenderPassCreateInfo& info);
			static RenderPass *ptrCreate(const RenderPassCreateInfo& info);

			~RenderPass();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_RENDERPASS_HPP_
