//
// Created by kisly on 01.09.2025.
//

#ifndef VK_INSTANCE_HPP_
#define VK_INSTANCE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/types.hpp"
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		/// @brief структура с информацией для создания экземпляра Vulkan
		struct InstanceInfo
		{
			/// @brief объект структуры version3 (версия Vulkan)
			version3 VULKAN_API_VERSION = {1, 2, 0};

			/// @brief объект структуры version3 (версия приложения, необязательный пармаетр)
			version3 APP_VERSION = {1, 0, 0};

			/// @brief название приложения (необязатяльный параметр)
			const char* APP_NAME = "CoreGL";

			/// @brief разрешить выводить дерево ресурсов vulkan при вызове функций
			bool debugApiDump = false;
		};

		/// @brief класс экземпляр Vulkan
		class Instance
		{
		private:
			friend class PhysicalDevices;
			friend class Surface;

			VkInstance instance{};

			explicit Instance(const InstanceInfo& info);

		public:
			/// @brief создаёт экземпляр Vulkan
			/// @param info объект структуры vulkan::InstanceInfo
			/// @return объект класса vulkan::Instance
			static Instance create(const InstanceInfo& info = {});

			/// @brief создаёт экземпляр Vulkan
			/// @param info объект структуры vulkan::InstanceInfo
			/// @return указатель на объект класса vulkan::Instance
			static Instance* PtrCreate(const InstanceInfo& info = {});

			~Instance();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_INSTANCE_HPP_



