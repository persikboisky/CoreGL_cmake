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

#define CODE_FAILED_INIT_GLFW 0
#define CODE_FAILED_INIT_WINDOW 1
#define CODE_FAILED_INIT_GLEW 2
#define CODE_FAILED_LOAD_IMAGE 3
#define CODE_FAILED_CHECK_KEY 4
#define CODE_FAILED_CREATE_CUSTOM_CURSOR 5
#define CODE_FAILED_OPEN_FILE 6
#define CODE_FAILED_CREATE_VERTEX_SHADER 7
#define CODE_FAILED_CREATE_FRAGMENT_SHADER 8
#define CODE_FAILED_CREATE_SHADER_PROGRAM 9
#define CODE_FAILED_BIND_VAO 12
#define CODE_FAILED_CREATE_VAO 13
#define CODE_FAILED_CREATE_VBO 14
#define CODE_FAILED_ADD_ATTRIBUTE_TO_VAO 15
#define NONE_CODERS 35
#define CODE_FAILED_PARSING_JSON 53

namespace core
{
    /// @brief класс для обработки исключений
    class Coders
    {
    private:
        std::string  info;
        int code;

    public:
        /// @brief конструктор для создания объекта ошибки
        /// @param codeError код ошибки
        /// @param addInfo доп. информайия, если требуется
        Coders(int codeError, std::string addInfo = "");

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
