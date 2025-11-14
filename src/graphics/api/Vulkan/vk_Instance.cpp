#include "vk_Instance.hpp"
#include "vk_Instance.hpp"
//
// Created by kisly on 01.09.2025.
//

#include "vk_Instance.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/coders.hpp"
#include "../../../util/console.hpp"
#include "../../../config.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

namespace core::vulkan
{
	Instance::Instance(const InstanceInfo& info)
	{
		VkApplicationInfo appInfo = {};
		appInfo.apiVersion = VK_MAKE_API_VERSION(
			0,
			info.vulkanVersion.MAJOR,
			info.vulkanVersion.MINOR,
			info.vulkanVersion.PATCH
		);
		appInfo.applicationVersion = VK_MAKE_VERSION(
			info.appVersion.MAJOR,
			info.appVersion.MINOR,
			info.appVersion.PATCH
		);
		appInfo.engineVersion = VK_VERSION_1_0;
		appInfo.pApplicationName = info.appName;
		appInfo.pEngineName = nullptr;
		appInfo.pNext = nullptr;
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

		VkInstanceCreateInfo instanceCreateInfo = {};
		instanceCreateInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(
			&instanceCreateInfo.enabledExtensionCount
		);

		std::vector<const char*> nameValidationLayer = {};
		nameValidationLayer.push_back("VK_LAYER_KHRONOS_validation");

		instanceCreateInfo.ppEnabledLayerNames = nameValidationLayer.data();
		instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(nameValidationLayer.size());
		instanceCreateInfo.flags = 0;
		instanceCreateInfo.pApplicationInfo = &appInfo;
		instanceCreateInfo.pNext = nullptr;
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

		VkResult result = vkCreateInstance(
			&instanceCreateInfo,
			nullptr,
			&this->instance);
		coders::vulkanProcessingError(result);

		if (CORE_INFO)
		{
			console::printTime();
			std::cout << "Ok: create vulkan instance" << std::endl;
		}
	}

	Instance Instance::create(const InstanceInfo& info)
	{
		return Instance(info);
	}

	Instance *Instance::ptrCreate(const InstanceInfo& info)
	{
		return new Instance(info);
	}

	Instance::~Instance()
	{
		vkDestroyInstance(this->instance, nullptr);
	}
}

#endif // defined(CORE_INCLUDE_VULKAN)
