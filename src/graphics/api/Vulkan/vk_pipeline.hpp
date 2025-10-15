//
// Created by kisly on 05.09.2025.
//

#ifndef VK_PIPELINE_HPP_
#define VK_PIPELINE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/types.hpp"
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct PushConstantInfo
		{
			SHADER_STAGES shaderStages = VERTEX_FRAGMENT_STAGES;
			uint32_t sizeOfBytes = 0;
			uint32_t offset = 0;
		};

		struct PipelineInfo
		{
			class Device* ptrDevice = nullptr;
			class ShaderProgram* ptrShaderProgram = nullptr;
			class RenderPass* ptrRenderPass = nullptr;

			size2i sizeViewport = {600, 600};
			pos2i posViewport = {0, 0};

			float maxDepth = 1.0f;
			float minDepth = 0.0;

			vulkan::PRIMITIVE primitive = vulkan::TRIANGLE_STRIP;
			TYPE_CULL_FACE typeCullFace = CULL_BACK;
			POLYGON_MODE polygonMode = POLYGON_FILL;
			FRONT_FACE frontFace = FRONT_FACE_COUNTER_CLOCKWISE;

			uint32_t pushConstantCount = 0;
			PushConstantInfo *ptrPushConstants = nullptr;

			uint32_t vertexBuffersCount = 0;
			class VertexBuffer* ptrVertexBuffers = nullptr;
		};

		class Pipeline
		{
		 private:
			VkPipeline pipeline;
			VkPipelineLayout pipelineLayout;

			VkDevice *ptrDevice = nullptr;

			explicit Pipeline(const PipelineInfo& info);

		 public:
			static Pipeline create(const PipelineInfo& info);
			static Pipeline *ptrCreate(const PipelineInfo& info);

			~Pipeline();

			VkPipeline getVkPipeline();
			VkPipeline *getVkPtrPipeline();

			VkPipelineLayout getVkPipelineLayout();
			VkPipelineLayout *getVkPtrPipelineLayout();
		};

	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_PIPELINE_HPP_
