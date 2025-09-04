//
// Created by kisly on 04.09.2025.
//

#ifndef VK_SURFACE_HPP_
#define VK_SURFACE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	class Window;
	namespace vulkan
	{
		class Surface
		{
		 private:
			VkSurfaceKHR surface;
			VkInstance* ptrInstance = nullptr;

			Surface(class Instance& instance, Window& window);

		 public:
			static Surface create(class Instance& instance, Window& window);
			static Surface *ptrCreate(class Instance& instance, Window& window);

			~Surface();

			VkSurfaceKHR getVkSurfaceKHR();
			VkSurfaceKHR *getVkPtrSurfaceKHR();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_SURFACE_HPP_
