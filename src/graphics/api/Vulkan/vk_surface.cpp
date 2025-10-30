//
// Created by kisly on 04.09.2025.
//

#include "vk_surface.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../window/Window.hpp"
#include "vk_Instance.hpp"
#include "../../../util/coders.hpp"
#include "../../../util/console.hpp"
#include "../../../config.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>

namespace core
{
	namespace vulkan
	{
		Surface::Surface(Instance& instance, Window& window) : ptrInstance(&instance.instance)
		{
			VkResult result = glfwCreateWindowSurface(
				instance.instance,
				window.getWindowOBJ(),
				nullptr,
				&this->surface);
			coders::vulkanProcessingError(result);

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "Ok: create window surface" << std::endl;
			}
		}

		Surface Surface::create(Instance& instance, Window& window)
		{
			return Surface(instance, window);
		}

		Surface* Surface::ptrCreate(Instance& instance, Window& window)
		{
			return new Surface(instance, window);
		}

		Surface::~Surface()
		{
			vkDestroySurfaceKHR(*this->ptrInstance, this->surface, nullptr);
		}

		VkSurfaceKHR Surface::getVkSurfaceKHR()
		{
			return this->surface;
		}

		VkSurfaceKHR* Surface::getVkPtrSurfaceKHR()
		{
			return &this->surface;
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)