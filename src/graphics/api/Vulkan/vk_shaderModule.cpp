//
// Created by kisly on 04.09.2025.
//

#include "vk_shaderModule.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/coders.hpp"
#include "../../../config.hpp"
#include "../../../util/console.hpp"
#include "vk_device.hpp"
#include <fstream>
#include <iostream>

namespace core::vulkan
{
	VkShaderModule ShaderModule::createShaderModule(VkDevice device, const char* path)
	{
		std::ifstream file(path, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			throw coders(6, path);
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();

		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = buffer.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(buffer.data());
		createInfo.flags = 0;
		createInfo.pNext = nullptr;

		VkShaderModule shaderModule;
		VkResult result = vkCreateShaderModule(
			device,
			&createInfo,
			nullptr,
			&shaderModule);
		coders::vulkanProcessingError(result);

		if (CORE_INFO)
		{
			console::printTime();
			std::cout << "Ok: create shader from path: " << path << std::endl;
		}

		return shaderModule;
	}

	ShaderModule::ShaderModule(const ShaderModuleInfo& info) : device(info.device->getPtrDevice())
	{
		if (info.pathToVertexShaderCode != nullptr)
		{

			this->shader.push_back(this->createShaderModule(info.device->getDevice(), info.pathToVertexShaderCode));
			this->nameFunc.push_back(info.nameMainFuncToVertexShader);

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "Ok: create vertex shader module" << std::endl;
			}
		}

		if (info.pathToFragmentShaderCode != nullptr)
		{
			this->shader.push_back(this->createShaderModule(info.device->getDevice(), info.pathToFragmentShaderCode));
			this->nameFunc.push_back(info.nameMainFuncToFragmentShader);

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "Ok: create fragment shader module" << std::endl;
			}
		}

		if (info.pathToGeometryShaderCode != nullptr)
		{
			this->shader.push_back(this->createShaderModule(info.device->getDevice(), info.pathToGeometryShaderCode));
			this->nameFunc.push_back(info.nameMainFuncToGeometryShader);

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "Ok: create geometry shader module" << std::endl;
			}
		}
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
		for (const VkShaderModule &shader : this->shader)
		{
			vkDestroyShaderModule(*this->device, shader, nullptr);
		}
	}
}

#endif //defined(CORE_INCLUDE_VULKAN)






