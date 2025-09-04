//
// Created by kisly on 01.09.2025.
//

#include "vk_Instance.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../config.hpp"
#include "../../../util/coders.hpp"
#include "../../../util/console.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

namespace core
{
	namespace vulkan
	{
		Instance::Instance(const instanceInfo& info)
		{
			VkApplicationInfo appInfo = {};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pNext = nullptr;
			appInfo.apiVersion = VK_MAKE_API_VERSION(
				0,
				info.VULKAN_API_VERSION.MAJOR,
				info.VULKAN_API_VERSION.MINOR,
				info.VULKAN_API_VERSION.PATCH);

			appInfo.applicationVersion = VK_MAKE_VERSION(
				info.APP_VERSION.MAJOR,
				info.APP_VERSION.MINOR,
				info.APP_VERSION.PATCH);

			appInfo.engineVersion = VK_VERSION_1_0;
			appInfo.pApplicationName = info.APP_NAME;
			appInfo.pEngineName = nullptr;

			VkInstanceCreateInfo instInfo = {};
			instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instInfo.pNext = nullptr;
			instInfo.flags = 0;
			instInfo.pApplicationInfo = &appInfo;
			instInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&instInfo.enabledExtensionCount);

			std::vector<const char*> nameValidationLayer = {};
			if (CORE_INFO) nameValidationLayer.push_back("VK_LAYER_KHRONOS_validation");
			if (info.debugApiDump) nameValidationLayer.push_back("VK_LAYER_LUNARG_api_dump");
			instInfo.ppEnabledLayerNames = nameValidationLayer.data();
			instInfo.enabledLayerCount = static_cast<uint32_t>(nameValidationLayer.size());

			VkResult result = vkCreateInstance(&instInfo, nullptr, &this->instance);
			coders::vulkanProcessingError(result);

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "Ok: create Vulkan instance" << std::endl;
			}
		}

		Instance Instance::create(const instanceInfo& info)
		{
			return Instance(info);
		}

		[[maybe_unused]] Instance* Instance::PtrCreate(const instanceInfo& info)
		{
			return new Instance(info);
		}

		Instance::~Instance()
		{
			vkDestroyInstance(this->instance, nullptr);
		}

		[[maybe_unused]] VkInstance Instance::getVkInstance()
		{
			return this->instance;
		}

		[[maybe_unused]] VkInstance* Instance::getVkPtrInstance()
		{
			return &this->instance;
		}
	} // culkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)