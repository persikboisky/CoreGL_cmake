//
// Created by kisly on 04.09.2025.
//

#ifndef VK_SHADERMODULE_HPP_
#define VK_SHADERMODULE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/types.hpp"
#include <vulkan/vulkan.h>
#include <vector>

namespace core::vulkan
{
	struct ShaderModuleInfo
	{
		bool flagCompile = false;
		const char* path = nullptr;
		const char* mainFuncName = "";
		TYPE_SHADER typeShader = {};
		class Device *ptrDevice = nullptr;
	};

	class ShaderModule
	{
	private:
		VkShaderModule shader = {};
		VkDevice *ptrDevice = nullptr;
		const char* mainFuncName = "";
		TYPE_SHADER typeShader = {};

		explicit ShaderModule(ShaderModuleInfo& info);

	public:
		static ShaderModule create(ShaderModuleInfo& info);
		static ShaderModule *ptrCreate(ShaderModuleInfo& info);

		~ShaderModule();

		const char* getNameMainFunc();
		VkShaderModule getVkShaderModule() const;

		TYPE_SHADER getTypeShader() const;
	};

	struct ShaderProgramInfo
	{
		ShaderModule** ptrShaders = nullptr;
		unsigned int count = 0;
	};

	class ShaderProgram
	{
	private:
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages = {};

		explicit ShaderProgram(ShaderProgramInfo& info);

	public:
		~ShaderProgram() = default;

		static ShaderProgram create(ShaderProgramInfo& info);
		static ShaderProgram *ptrCreate(ShaderProgramInfo& info);

		std::vector<VkPipelineShaderStageCreateInfo> getVkPipelineShaderStageCreateInfos();
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_SHADERMODULE_HPP_
