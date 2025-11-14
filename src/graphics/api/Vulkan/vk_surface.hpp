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
		/// @brief класс поверхности окна(холст)
		class Surface
		{
		protected:
			friend class Device;
			friend class SwapChain;

		private:
			VkSurfaceKHR surface;
			VkInstance* ptrInstance = nullptr;

			Surface(class Instance& instance, Window& window);

		public:
			/// @brief создаёт поверхность окна
			/// @param instance объект класса vulkan::Instance
			/// @param window объект класса Window
			/// @return объект класса vulkan::Surface
			static Surface create(class Instance& instance, Window& window);

			/// @brief создаёт поверхность окна
			/// @param instance объект класса vulkan::Instance
			/// @param window объект класса Window
			/// @return указатель на объект класса vulkan::Surface
			static Surface* ptrCreate(class Instance& instance, Window& window);

			~Surface();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_SURFACE_HPP_