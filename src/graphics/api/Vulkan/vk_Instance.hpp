//
// Created by kisly on 01.09.2025.
//

#ifndef VK_INSTANCE_HPP_
#define VK_INSTANCE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../types/apiTypes.hpp"
#include <vulkan/vulkan.h>

namespace core::vulkan
{
	/// @brief структура для передачи параметров создания экземпляра vulkan
	struct InstanceCreateInfo
	{
		/// @brief название вашего приложения(необязательно, по умолчанию nullptr)
		const char* appName = "CoreGL";

		/// @brief версия вашего приложения(необязательно)
		Version3 appVersion = { 1, 0, 0 };

		/// @brief версия vulkan(необязательно)
		Version3 vulkanVersion = { 1, 2, 0 };
	};

	/// @brief класс экземпляра vulkan
	class Instance
	{
	protected:
		friend class Surface;
		friend class PhysicalDevices;

	private:
		VkInstance instance = {};

		explicit Instance(const InstanceCreateInfo& info);

	public:
		/// @brief создаёт экземпляр vulkan 
		/// @param info объект структуры core::vulkan::InstanceCreateInfo
		/// @return объект класса core::vulkan::Instance
		static Instance create(const InstanceCreateInfo& info);

		/// @brief создаёт экземпляр vulkan 
		/// @param info объект структуры core::vulkan::InstanceCreateInfo
		/// @return указаетль на объект класса core::vulkan::Instance
		static Instance *ptrCreate(const InstanceCreateInfo& info);

		~Instance();
	};
}

#endif // defined(CORE_INCLUDE_VULKAN)
#endif // VK_INSTANCE_HPP_
