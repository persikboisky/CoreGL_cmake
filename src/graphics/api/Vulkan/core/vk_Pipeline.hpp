//
// Created by kisly on 07.09.2025.
//

#ifndef VK_PIPELINE_HPP
#define VK_PIPELINE_HPP

#include "../../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../../types/apiTypes.hpp"
#include <vector>
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct GraphicsPipelineCreateInfo
		{
			class Device* ptrDevice = nullptr;
			class RenderPass* ptrRenderPass = nullptr;
		    uint32_t subpass = 0;
			class PipelineLayout* ptrPipelineLayout = nullptr;
			struct PipelineVertexInputInfo* ptrPipelineVertexInputInfo = nullptr;

			std::vector<class ShaderModule*> ptrShaderModules = {};
			std::vector<DYNAMIC_STATE> dynamicState = {};

			Rect2D scissor = {};
			Viewport viewport = {};

			vulkan::PRIMITIVE primitive = PRIMITIVE::TRIANGLE_LIST;
			POLYGON_MODE polygonMode = POLYGON_MODE::FILL;
			CULL_MODE cullFace = CULL_MODE::NONE;
			FRONT_FACE frontFace = FRONT_FACE::COUNTER_CLOCKWISE;

			bool flagDepthTest = false;
		};

		struct PipelinePushConstantInfo
		{
			uint32_t offset = 0;
			uint32_t size = 0;
			vulkan::SHADER_STAGES shaderStages = VERTEX_STAGE;
		};

		struct PipelineLayoutInfo
		{
			class Device* ptrDevice = nullptr;
			std::vector<PipelinePushConstantInfo> vecPushConstantInfos = {};
			std::vector<class DescriptorSetLayout*> vecPtrDescriptorSetsLayouts = {};
		};

		struct PipelineVertexAttributeDescription
		{
			uint32_t binding = 0;
			uint32_t offset = 0;
			uint32_t location = 0;
			vulkan::FORMAT_VARIABLE format = FLOAT;
		};

		struct PipelineVertexBindingDescriptions
		{
			uint32_t binding = 0;
			uint32_t sizeVertex = 0;
		};

		struct PipelineVertexInputInfo
		{
			std::vector<PipelineVertexAttributeDescription> vecVertexAttributeDescriptions = {};
			std::vector<PipelineVertexBindingDescriptions> vecVertexBindingDescriptions = {};
		};

		class PipelineLayout
		{
		protected:
			friend class GraphicsPipeline;
			friend class CommandBuffer;
		    friend class ComputePipeline;

		private:
			VkPipelineLayout layout = {};
			VkDevice* ptrDevice = nullptr;

            explicit PipelineLayout(const PipelineLayoutInfo& info);

		public:
			~PipelineLayout();

			static PipelineLayout create(const PipelineLayoutInfo& info);
			static PipelineLayout *ptrCreate(const PipelineLayoutInfo& info);
		};

		class GraphicsPipeline
		{
		protected:
			friend class CommandBuffer;

		private:
			VkDevice* ptrDevice = nullptr;
			VkPipeline pipeline = nullptr;

            explicit GraphicsPipeline(const GraphicsPipelineCreateInfo& info);

		public:
			static GraphicsPipeline create(const GraphicsPipelineCreateInfo& info);
			static GraphicsPipeline *ptrCreate(const GraphicsPipelineCreateInfo& info);

			~GraphicsPipeline();
		};

	    struct ComputePipelineCreateInfo
	    {
	        class Device* ptrDevice = nullptr;
	        class ShaderModule* ptrShaderModule = nullptr;
	        class PipelineLayout* ptrPipelineLayout = nullptr;
	    };

		class ComputePipeline
		{
		private:
		    VkDevice* ptrDevice = nullptr;
		    VkPipeline pipeline = nullptr;

            explicit ComputePipeline(const ComputePipelineCreateInfo& info);

		public:
		    ~ComputePipeline();

		    static ComputePipeline create(const ComputePipelineCreateInfo& info);
		    static ComputePipeline *ptrCreate(const ComputePipelineCreateInfo& info);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_PIPELINE_HPP
