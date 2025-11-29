//
// Created by kisly on 07.09.2025.
//

#include "vk_ShaderStage.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Device.hpp"
#include "../../../util/coders.hpp"
#include "../../../util/console.hpp"
#include "../../../config.hpp"
#include <fstream>
#include <vector>
#include <iostream>

namespace core
{
	namespace vulkan
	{
		VkShaderStageFlags ShaderModule::convertStage(const SHADER_STAGES& stages)
		{
			return (stages == SHADER_STAGES::VERTEX_STAGE) ? VK_SHADER_STAGE_VERTEX_BIT :
				   (stages == SHADER_STAGES::FRAGMENT_STAGE) ? VK_SHADER_STAGE_FRAGMENT_BIT :
				   (stages == SHADER_STAGES::GEOMETRY_STAGE) ? VK_SHADER_STAGE_GEOMETRY_BIT :
				   (stages == SHADER_STAGES::VERTEX_FRAGMENT_STAGES) ? VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT:
				   (stages == SHADER_STAGES::VERTEX_GEOMETRY_FRAGMENT_STAGES) ? VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_GEOMETRY_BIT:
				   VK_SHADER_STAGE_ALL;
		}

		VkShaderStageFlagBits ShaderModule::convertType(const TYPE_SHADER& type)
		{
			return (type == TYPE_SHADER::VERTEX) ? VK_SHADER_STAGE_VERTEX_BIT :
				   (type == TYPE_SHADER::FRAGMENT) ? VK_SHADER_STAGE_FRAGMENT_BIT :
				   VK_SHADER_STAGE_GEOMETRY_BIT;
		}

		ShaderModule::ShaderModule(const ShaderModuleInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			std::ifstream file(info.filename, std::ios::ate | std::ios::binary);
			if (!file.is_open())
				throw coders(6, info.filename);

			size_t fileSize = (size_t)file.tellg();
			std::vector<char> buffer(fileSize);

			file.seekg(0);
			file.read(buffer.data(), static_cast<std::streamsize>(fileSize));
			file.close();

			file.close();

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "OK: read file: " << info.filename << std::endl;
			}

			VkShaderModuleCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.codeSize = buffer.size();
			createInfo.pCode = reinterpret_cast<const uint32_t*>(buffer.data());

			VkResult result = vkCreateShaderModule(
					info.ptrDevice->device,
					&createInfo,
					nullptr,
					&shaderModule);
			coders::vulkanProcessingError(result);

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "OK: create vulkan shader module" << std::endl;
			}

			this->stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			this->stage.stage = convertType(info.type);
			this->stage.module = this->shaderModule;
			this->stage.flags = 0;
			this->stage.pNext = nullptr;
			this->stage.pName = info.MainFunctionName;
			this->stage.pSpecializationInfo = nullptr;
		}

		ShaderModule ShaderModule::create(const ShaderModuleInfo& info)
		{
			return ShaderModule(info);
		}

		ShaderModule* ShaderModule::ptrCreate(const ShaderModuleInfo& info)
		{
			return new ShaderModule(info);
		}

		ShaderModule::~ShaderModule()
		{
			vkDestroyShaderModule(*this->ptrDevice, this->shaderModule, nullptr);
		}

	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

