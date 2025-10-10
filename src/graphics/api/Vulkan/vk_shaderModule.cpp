//
// Created by kisly on 04.09.2025.
//

#include "vk_shaderModule.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/coders.hpp"
#include "../../../config.hpp"
#include "../../../util/console.hpp"
#include "../../../file/code.hpp"
#include "vk_device.hpp"
//#include <shaderc/shaderc.hpp>
#include <fstream>
#include <iostream>

namespace core::vulkan
{
	ShaderModule::ShaderModule(ShaderModuleInfo& info) :
		typeShader(info.typeShader), ptrDevice(info.ptrDevice->getPtrDevice()),
		mainFuncName(info.mainFuncName)
	{
		VkShaderModuleCreateInfo createInfo = {};
		std::vector<char> buffer = {};
		std::vector<uint32_t> spirv = {};

		if (!info.flagCompile)
		{
			std::ifstream file(info.path, std::ios::ate | std::ios::binary);

			if (!file.is_open())
			{
				throw coders(6, info.path);
			}

			size_t fileSize = (size_t)file.tellg();
			buffer.resize(fileSize);

			file.seekg(0);
			file.read(buffer.data(), (std::streamsize)fileSize);
			file.close();
		}
		else
		{
//			shaderc::Compiler compiler;
//			shaderc::CompileOptions options;
//
//			options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_0);
//			options.SetOptimizationLevel(shaderc_optimization_level_performance);
		}

		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = { (!info.flagCompile) ?
								buffer.size() :
								spirv.size()
		};
		createInfo.pCode = { (!info.flagCompile) ?
							 reinterpret_cast<const uint32_t*>(buffer.data()) :
							 spirv.data()
		};
		createInfo.flags = 0;
		createInfo.pNext = nullptr;

		VkResult result = vkCreateShaderModule(
				info.ptrDevice->getDevice(),
				&createInfo,
				nullptr,
				&this->shader);
		coders::vulkanProcessingError(result);

		if (CORE_INFO)
		{
			console::printTime();
			std::cout << "Ok: compile shader module, path: " << info.path << std::endl;
		}
	}

	ShaderModule ShaderModule::create(ShaderModuleInfo& info)
	{
		return ShaderModule(info);
	}

	ShaderModule* ShaderModule::ptrCreate(ShaderModuleInfo& info)
	{
		return new ShaderModule(info);
	}

	ShaderModule::~ShaderModule()
	{
		vkDestroyShaderModule(
				*this->ptrDevice,
				this->shader,
				nullptr);
	}

	const char* ShaderModule::getNameMainFunc()
	{
		return this->mainFuncName;
	}

	VkShaderModule ShaderModule::getVkShaderModule() const
	{
		return this->shader;
	}

	TYPE_SHADER ShaderModule::getTypeShader() const
	{
		return this->typeShader;
	}

	ShaderProgram::ShaderProgram(ShaderProgramInfo& info)
	{
		this->shaderStages.resize(info.count);
		for (unsigned int i = 0; i < info.count; i++)
		{
			this->shaderStages[i].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			this->shaderStages[i].module = info.ptrShaders[i]->getVkShaderModule();
			this->shaderStages[i].pName = info.ptrShaders[i]->getNameMainFunc();

			switch (TYPE_SHADER(info.ptrShaders[i]->getTypeShader()))
			{
			case FRAGMENT:
				this->shaderStages[i].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
				break;
			case GEOMETRY:
				this->shaderStages[i].stage = VK_SHADER_STAGE_GEOMETRY_BIT;
				break;
			case VERTEX:
				this->shaderStages[i].stage = VK_SHADER_STAGE_VERTEX_BIT;
				break;
			}
		}
	}

	ShaderProgram ShaderProgram::create(ShaderProgramInfo& info)
	{
		return ShaderProgram(info);
	}

	std::vector<VkPipelineShaderStageCreateInfo> ShaderProgram::getVkPipelineShaderStageCreateInfos()
	{
		return this->shaderStages;
	}

	ShaderProgram *ShaderProgram::ptrCreate(ShaderProgramInfo& info)
	{
		return new ShaderProgram(info);
	}
}

#endif //defined(CORE_INCLUDE_VULKAN)






