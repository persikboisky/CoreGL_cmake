//
// Created by kisly on 05.09.2025.
//

#include "vk_pipeline.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "../../../util/coders.hpp"
#include "vk_shaderModule.hpp"
#include "vk_renderPass.hpp"
#include "vk_vertexBuffer.hpp"
#include <array>
#include <iostream>

namespace core
{
	namespace vulkan
	{
		Pipeline::Pipeline(const pipelineInfo &info) : ptrDevice(info.ptrDevice->getPtrDevice())
		{
			VkPipelineLayoutCreateInfo layoutInfoCreateInfo = {};
			layoutInfoCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			layoutInfoCreateInfo.flags = 0;
			layoutInfoCreateInfo.pNext = nullptr;

			layoutInfoCreateInfo.pSetLayouts = nullptr;
			layoutInfoCreateInfo.setLayoutCount = 0;

			std::vector<VkPushConstantRange> pushConstantRanges = {};
			for (uint32_t index = 0; index < info.pushConstantCount; index++)
			{
				VkShaderStageFlags shaderStageFlagBits;
				switch (info.ptrPushConstants[index].shaderStages)
				{
				case VERTEX_STAGE:
					shaderStageFlagBits = VK_SHADER_STAGE_VERTEX_BIT;
					break;
				case FRAGMENT_STAGE:
					shaderStageFlagBits = VK_SHADER_STAGE_FRAGMENT_BIT;
					break;
				case GEOMETRY_STAGE:
					shaderStageFlagBits = VK_SHADER_STAGE_GEOMETRY_BIT;
					break;
				case VERTEX_FRAGMENT_STAGES:
					shaderStageFlagBits = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;
					break;
				case VERTEX_GEOMETRY_FRAGMENT_STAGES:
					shaderStageFlagBits =
						VK_SHADER_STAGE_FRAGMENT_BIT |
						VK_SHADER_STAGE_VERTEX_BIT |
						VK_SHADER_STAGE_GEOMETRY_BIT;
					break;
				default:
					shaderStageFlagBits = VK_SHADER_STAGE_ALL;
					break;
				}

				pushConstantRanges.push_back({.stageFlags = shaderStageFlagBits,
											  .offset = info.ptrPushConstants[index].offset,
											  .size = info.ptrPushConstants[index].sizeOfBytes});
			}

			if (info.pushConstantCount > 0)
			{
				layoutInfoCreateInfo.pushConstantRangeCount = info.pushConstantCount;
				layoutInfoCreateInfo.pPushConstantRanges = pushConstantRanges.data();
			}
			else
			{
				layoutInfoCreateInfo.pushConstantRangeCount = 0;
				layoutInfoCreateInfo.pPushConstantRanges = nullptr;
			}

			VkResult result = vkCreatePipelineLayout(
				info.ptrDevice->getDevice(),
				&layoutInfoCreateInfo,
				nullptr,
				&this->pipelineLayout);
			coders::vulkanProcessingError(result);

			//--------------------------------------------------------------------------------------------------
			// Смешивание цветов
			VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
												  VK_COLOR_COMPONENT_G_BIT |
												  VK_COLOR_COMPONENT_B_BIT |
												  VK_COLOR_COMPONENT_A_BIT;

			VkPipelineColorBlendStateCreateInfo colorBlending = {};
			colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			colorBlending.logicOpEnable = VK_FALSE;
			colorBlending.logicOp = VK_LOGIC_OP_COPY;
			colorBlending.attachmentCount = 1;
			colorBlending.pAttachments = &colorBlendAttachment;
			colorBlending.blendConstants[0] = 0.0f;
			colorBlending.blendConstants[1] = 0.0f;
			colorBlending.blendConstants[2] = 0.0f;
			colorBlending.blendConstants[3] = 0.0f;

			//--------------------------------------------------------------------------------------------------
			// Входной сборщик вершин
			VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
			inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			inputAssembly.pNext = nullptr;
			inputAssembly.flags = 0;

			VkPrimitiveTopology primitive;
			switch (info.primirive)
			{
			case TRIANGLE_STRIP:
				primitive = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
				break;
			case TRIANGLE_LIST:
				primitive = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				break;
			case LINE_STRIP:
				primitive = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
				break;
			case LINE_LIST:
				primitive = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
				break;
			case TRIANGLE_FAN:
				primitive = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
				break;
			default:
				primitive = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
				break;
			}

			inputAssembly.topology = primitive;

			//--------------------------------------------------------------------------------------------------
			// Мультисэмплинг
			VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
			multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
			multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
			multisampleStateCreateInfo.minSampleShading = 1.0f;
			multisampleStateCreateInfo.pSampleMask = nullptr;
			multisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
			multisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;

			//--------------------------------------------------------------------------------------------------
			// Шейдерные стадии
			VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
			vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
			vertShaderStageInfo.module = info.ptrShaderModule->getShaders()[0];
			vertShaderStageInfo.pName = info.ptrShaderModule->getNamesFuncToShaders()[0];

			VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
			fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
			fragShaderStageInfo.module = info.ptrShaderModule->getShaders()[1];
			fragShaderStageInfo.pName = info.ptrShaderModule->getNamesFuncToShaders()[1];

			std::vector<VkPipelineShaderStageCreateInfo> shaderStages = {vertShaderStageInfo, fragShaderStageInfo};

			if (info.ptrShaderModule->getShaders().size() > 2)
			{
				VkPipelineShaderStageCreateInfo geomShaderStageInfo{};
				geomShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				geomShaderStageInfo.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
				geomShaderStageInfo.module = info.ptrShaderModule->getShaders()[2];
				geomShaderStageInfo.pName = info.ptrShaderModule->getNamesFuncToShaders()[2];
				shaderStages.push_back(geomShaderStageInfo);
			}

			//--------------------------------------------------------------------------------------------------
			// Растеризация
			VkCullModeFlags cullMode;
			switch (info.typeCullFace)
			{
			case CULL_BACK:
				cullMode = VK_CULL_MODE_BACK_BIT;
				break;

			case CULL_FRONT:
				cullMode = VK_CULL_MODE_FRONT_BIT;
				break;

			case CULL_FRONT_AND_BACK:
				cullMode = VK_CULL_MODE_FRONT_AND_BACK;
				break;

			case CULL_NONE:
				cullMode = VK_CULL_MODE_NONE;
				break;
			}

			VkPolygonMode polygonMode;
			switch (info.polygonMode)
			{
			case POLYGON_FILL:
				polygonMode = VK_POLYGON_MODE_FILL;
				break;
			case POLYGON_LINE:
				polygonMode = VK_POLYGON_MODE_LINE;
				break;
			case POLYGON_POINT:
				polygonMode = VK_POLYGON_MODE_POINT;
				break;
			}

			VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
			rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			rasterizationStateCreateInfo.cullMode = cullMode; // Режим отсечения граней (отсекаем не лецивые грани)
			rasterizationStateCreateInfo.depthBiasClamp = 0;
			rasterizationStateCreateInfo.depthBiasConstantFactor = 0;
			rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
			rasterizationStateCreateInfo.depthBiasSlopeFactor = 0;
			rasterizationStateCreateInfo.depthClampEnable = VK_TRUE;
			rasterizationStateCreateInfo.flags = 0;
//			rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE; // ПРОТИВ ЧАСОВОЙ СТРЕЛКИ
			rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
			rasterizationStateCreateInfo.lineWidth = 1.0f;
			rasterizationStateCreateInfo.pNext = nullptr;
			rasterizationStateCreateInfo.polygonMode = polygonMode;
			rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;

			//--------------------------------------------------------------------------------------------------
			// вьюпорт
			VkViewport viewport = {};
			viewport.width = info.sizeViewport.width;
			viewport.height = info.sizeViewport.height;
			viewport.maxDepth = info.maxDepth;
			viewport.minDepth = info.minDepth;
			viewport.x = info.posViewport.x;
			viewport.y = info.posViewport.y;

			VkRect2D scissors = {};
			scissors.extent.width = info.sizeViewport.width;
			scissors.extent.height = info.sizeViewport.height;
			scissors.offset = {0, 0};

			VkPipelineViewportStateCreateInfo viewportStateCreateInfo = {};
			viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			viewportStateCreateInfo.flags = 0;
			viewportStateCreateInfo.pNext = nullptr;
			viewportStateCreateInfo.pScissors = &scissors;
			viewportStateCreateInfo.pViewports = &viewport;
			viewportStateCreateInfo.scissorCount = 1;
			viewportStateCreateInfo.viewportCount = 1;

			//--------------------------------------------------------------------------------------------------
			// входные вершины
			VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
			vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			vertexInputInfo.flags = 0;
			vertexInputInfo.pNext = nullptr;
			vertexInputInfo.pVertexBindingDescriptions = nullptr;
			vertexInputInfo.vertexBindingDescriptionCount = 0;
			vertexInputInfo.pVertexAttributeDescriptions = nullptr;
			vertexInputInfo.vertexAttributeDescriptionCount = 0;

			std::vector<VkVertexInputAttributeDescription> attributeDescriptions = {};
			std::vector<VkVertexInputBindingDescription> bindingDescription = {};

			if (info.vertexBuffersCount > 0 && info.ptrVertexBuffers != nullptr)
			{
				bindingDescription.resize(info.vertexBuffersCount);
				for (uint32_t i = 0; i < info.vertexBuffersCount; i++)
				{
					bindingDescription[i].binding = info.ptrVertexBuffers->getVkVertexInputBindingDescription().binding;
					bindingDescription[i].stride = info.ptrVertexBuffers->getVkVertexInputBindingDescription().stride;
					bindingDescription[i].inputRate = info.ptrVertexBuffers->getVkVertexInputBindingDescription().inputRate;
				}

				attributeDescriptions.resize(info.ptrVertexBuffers->getVkVertexInputAttributeDescriptions().size());
				for (uint32_t i = 0; i < info.ptrVertexBuffers->getVkVertexInputAttributeDescriptions().size(); i++)
				{
					attributeDescriptions[i].binding = info.ptrVertexBuffers->getVkVertexInputAttributeDescriptions()[i].binding;
					attributeDescriptions[i].location = info.ptrVertexBuffers->getVkVertexInputAttributeDescriptions()[i].location;
					attributeDescriptions[i].format = info.ptrVertexBuffers->getVkVertexInputAttributeDescriptions()[i].format;
					attributeDescriptions[i].offset = info.ptrVertexBuffers->getVkVertexInputAttributeDescriptions()[i].offset;
				}

				vertexInputInfo.pVertexBindingDescriptions = bindingDescription.data();
				vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescription.size());
				vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
				vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
			}

			//--------------------------------------------------------------------------------------------------
			// настройка теста глубины
			VkPipelineDepthStencilStateCreateInfo depthStencil = {};
			depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
			depthStencil.depthTestEnable = VK_TRUE;
			depthStencil.depthWriteEnable = VK_TRUE;
			depthStencil.depthBoundsTestEnable = VK_FALSE;
			depthStencil.stencilTestEnable = VK_FALSE;
			depthStencil.minDepthBounds = info.minDepth;
			depthStencil.maxDepthBounds = info.maxDepth;
			depthStencil.back = {};
			depthStencil.front = {};

			//--------------------------------------------------------------------------------------------------
			// конвейер
			VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
			pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
			pipelineCreateInfo.basePipelineIndex = 0;
			pipelineCreateInfo.flags = 0;
			pipelineCreateInfo.pNext = VK_NULL_HANDLE;
			pipelineCreateInfo.pTessellationState = VK_NULL_HANDLE;
			pipelineCreateInfo.layout = this->pipelineLayout;
			pipelineCreateInfo.pColorBlendState = &colorBlending;
			pipelineCreateInfo.pDepthStencilState = (info.ptrRenderPass->getStateDepth() == true) ? &depthStencil : VK_NULL_HANDLE;
			pipelineCreateInfo.pDynamicState = VK_NULL_HANDLE;
			pipelineCreateInfo.pInputAssemblyState = &inputAssembly;
			pipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
			pipelineCreateInfo.pStages = shaderStages.data();
			pipelineCreateInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
			pipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
			pipelineCreateInfo.pVertexInputState = &vertexInputInfo;
			pipelineCreateInfo.pViewportState = &viewportStateCreateInfo;
			pipelineCreateInfo.renderPass = info.ptrRenderPass->getVkRenderPass();
			pipelineCreateInfo.subpass = 0;

			result = vkCreateGraphicsPipelines(
				info.ptrDevice->getDevice(),
				VK_NULL_HANDLE,
				1,
				&pipelineCreateInfo,
				nullptr,
				&this->pipeline);
			coders::vulkanProcessingError(result);
		}

		Pipeline Pipeline::create(const pipelineInfo &info)
		{
			return Pipeline(info);
		}

		Pipeline *Pipeline::ptrCreate(const pipelineInfo &info)
		{
			return new Pipeline(info);
		}

		Pipeline::~Pipeline()
		{
			vkDestroyPipeline(
				*this->ptrDevice,
				this->pipeline,
				nullptr);

			vkDestroyPipelineLayout(
				*this->ptrDevice,
				this->pipelineLayout,
				nullptr);
		}

		VkPipeline Pipeline::getVkPipeline()
		{
			return this->pipeline;
		}

		VkPipeline *Pipeline::getVkPtrPipeline()
		{
			return &this->pipeline;
		}

		VkPipelineLayout Pipeline::getVkPipelineLayout()
		{
			return this->pipelineLayout;
		}

		VkPipelineLayout *Pipeline::getVkPtrPipelineLayout()
		{
			return &this->pipelineLayout;
		}
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
