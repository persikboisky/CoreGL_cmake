//
// Created by kisly on 04.09.2025.
//

#ifndef VK_PHYSICALDEVICES_HPP_
#define VK_PHYSICALDEVICES_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		/// @brief класс список графических видиокарт на вашем ПК
		class PhysicalDevices
		{
		 private:
			std::vector<VkPhysicalDevice> devices = {};

			explicit PhysicalDevices(class Instance& instance);

		 public:
			/// @brief получает список видиокарт
			/// @param instance объект класса vulkan::Instance
			/// @return объект класса vulkan::PhysicalDevices
			static PhysicalDevices get(class Instance& instance);

			/// @brief получает список видиокарт
			/// @param instance объект класса vulkan::Instance
			/// @return указатель нв объект класса vulkan::PhysicalDevices
			static PhysicalDevices* ptrGet(class Instance& instance);

			[[maybe_unused]] VkPhysicalDevice getVkPhysicalDevice(uint32_t id = 0);

			~PhysicalDevices() = default;
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_PHYSICALDEVICES_HPP_
