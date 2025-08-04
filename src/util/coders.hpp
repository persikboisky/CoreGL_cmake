//
// Created by kisly on 13.07.2025.
//

#ifndef CODERS_HPP
#define CODERS_HPP

#include "../modules.hpp"

#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#endif //defined(CORE_INCLUDE_VULKAN)

#include <string>

namespace core
{
    /// @brief класс для обработки исключений
    class coders
    {
    private:
        std::string  info;
        int code;

    public:
        /// @brief конструктор для создания объекта ошибки
        /// @param codeError код ошибки
        /// @param addInfo доп. информайия, если требуется
        coders(int codeError, std::string addInfo = "");

        /// @brief возвращает код ошибки (в файле CoreGL/src/util/coders.cpp есть массив INFO_CODERS - это список ошибок)
        /// @return код
        [[nodiscard]] int getCode() const;

        /// @brief возвращает информацию об ошибке
        /// @return строка
        [[nodiscard]] std::string getInfo();

        /// @brief выводит в консоль информацию об ошибке и её код
        void print();

#if defined(CORE_INCLUDE_VULKAN)
        static void vulkanProcessingError(const VkResult& result);
#endif //defined(CORE_INCLUDE_VULKAN)
    };
}

#endif //CODERS_HPP
