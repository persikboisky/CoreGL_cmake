//
// Created by kisly on 04.09.2025.
//

#ifndef VK_SHADERMODULE_HPP_
#define VK_SHADERMODULE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core::vulkan
{
	struct ShaderModuleInfo
	{
		class Device *device = nullptr;

		const char* pathToVertexShaderCode = nullptr;
		const char* nameMainFuncToVertexShader = "main";

		const char* pathToFragmentShaderCode = nullptr;
		const char* nameMainFuncToFragmentShader = "main";

		const char* pathToGeometryShaderCode = nullptr;
		const char* nameMainFuncToGeometryShader = "main";
	};

	class ShaderModule
	{
	 private:
		VkShaderModule createShaderModule(VkDevice device, const char* path);

		std::vector<VkShaderModule> shader = {};
		std::vector<const char*> nameFunc = {};

		VkDevice* device = nullptr;

		ShaderModule(const ShaderModuleInfo& info);

	 public:
		static ShaderModule create(const ShaderModuleInfo& info);
		static ShaderModule *ptrCreate(const ShaderModuleInfo& info);

		~ShaderModule();
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_SHADERMODULE_HPP_
