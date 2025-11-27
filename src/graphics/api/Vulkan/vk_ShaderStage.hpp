//
// Created by kisly on 07.09.2025.
//

#ifndef VK_SHADERPROGRAM_HPP
#define VK_SHADERPROGRAM_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <string>
#include "../../../util/types.hpp"

namespace core
{
	namespace vulkan
	{
		struct ShaderModuleInfo
		{
			class Device* ptrDevice = nullptr;
			std::string filename;
			TYPE_SHADER type;
			const char *MainFunctionName = "main";
		};

		class ShaderModule
		{
		protected:
			friend class PipelineLayout;
			friend class GraphicsPipeline;
			friend class DescriptorSetLayout;

		private:
			VkDevice *ptrDevice = nullptr;
			VkShaderModule shaderModule = {};
			VkPipelineShaderStageCreateInfo stage = {};

			static VkShaderStageFlags convertStage(const SHADER_STAGES& stages);
			static VkShaderStageFlagBits convertType(const TYPE_SHADER& type);

			ShaderModule(const ShaderModuleInfo& info);

		public:
			static ShaderModule create(const ShaderModuleInfo& info);
			static ShaderModule *ptrCreate(const ShaderModuleInfo& info);

			~ShaderModule();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_SHADERPROGRAM_HPP
