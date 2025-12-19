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
        enum class OPERATES_TYPE : int
        {
            GRAPHICS,
            COMPUTER,
            TRANSFER,
            PROTECTED,
            SPARSE_BINDING,
            VIDEO_DECODE,
            VIDEO_ENCODE,
        };

        /// @brief класс для хранения информации об видеокарте
        class PhysicalDeviceInfo
        {
        protected:
            friend class PhysicalDevices;
            friend class VertexBuffer;
            friend class ElementBuffer;

        private:
            VkPhysicalDevice physicalDevice = nullptr;
            VkPhysicalDeviceProperties deviceProperties = {};
            std::vector<VkQueueFamilyProperties> queueFamilies = {};

            PhysicalDeviceInfo(VkPhysicalDevice physicalDevice);

        public:
            /// @brief получает кол-во семейств очередей видеокарты
            /// @return кол-во семейств очередей
            uint32_t getQueueFamilyCount() const;

            /// @brief получает кол-во очередей из семействе очередей видеокарты
            /// @param queueFamilyIndex индекс семейства
            /// @return кол-во очередей
            uint32_t getQueueCount(uint32_t queueFamilyIndex) const;

            /// @brief выводит информацию о семействах очередей в консоль
            void printQueueFamilyInfo();

            /// @brief Получает минимальное поддерживаемое видеокартой кол-во изображений для цепочки показа (swapchain)
            /// @param surface холст окна (объект класса core::Surface)
            /// @return минимальное кол-во изображений
            uint32_t minImageCount(const class Surface& surface) const;
            
            /// @brief  Получает максимальное поддерживаемое видеокартой кол-во изображений для цепочки показа (swapchain)
            /// @param surface холст окна (объект класса core::Surface)
            /// @return максимальное кол-во изображений
            uint32_t maxImageCount(const class Surface& surface) const;

            /// @brief проверяет поддержку определённой операции семейством
            /// @param queueFamilyIndex индекс семейства
            /// @param type тип операции (пример OPERATES_TYPE::GRAPHICS(графические операции), OPERATES_TYPE::COMPUTER(вычисления))
            /// @return true - если поддерживает, иначе false
            bool checkOperationSupport(uint32_t queueFamilyIndex, const OPERATES_TYPE& type) const;

            /// @brief проверяет поддержку операции вывода изображения на холст семейством
            /// @param queueFamilyIndex индекс семейства
            /// @param surface холст
            /// @return true - если поддерживает, иначе false
            bool checkPresentOperationSupport(uint32_t queueFamilyIndex, const class Surface& surface) const;

            /// @brief получает индекс семейства очереди заданного типа
            /// @param type тип операции (пример OPERATES_TYPE::GRAPHICS(графические операции), OPERATES_TYPE::COMPUTER(вычисления))
            /// @return индекс семейства
            uint32_t getQueueFamilyIndex(const OPERATES_TYPE& type);

            /// @brief получает индекс семейства очереди способной к операции представления изображения
            /// @param surface холст
            /// @return индекс семейства
            uint32_t getPresentQueueFamilyIndex(const class Surface& surface);
        };

        /// @brief класс список графических видиокарт на вашем ПК
        class PhysicalDevices
        {
        protected:
            friend class Device;

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

            ~PhysicalDevices() = default;
            
            /// @brief возвращает информацию об выбранной видеокарте
            /// @param index индекс видеокарты
            /// @return объект core::vk::PhysicalDeviceInfo
            PhysicalDeviceInfo getDeviceInfo(uint32_t index) const;
        };
    } // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_PHYSICALDEVICES_HPP_