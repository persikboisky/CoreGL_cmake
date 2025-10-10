//
// Created by kisly on 14.07.2025.
//

#ifndef CODE_HPP
#define CODE_HPP

#include <string>

namespace core
{
    /// @brief класс для чтения текста из файла
    class code
    {
    private:
        std::string text;
        const char* path;

        code(const char* path);

    public:
        /// @brief читает файл
        /// @param path путь к файлу
        /// @return строку текста прочитанную из файла
        static std::string loadStr(const char* path);

        /// @brief читает файл
        /// @param path путь к файлу
        /// @return объект класса code
        static code load(const char* path);

        /// @brief получает прочитанную строку
        /// @return строку
        std::string getStr();

        /// @brief получает прочитанную строку
        /// @return си-строку
        const char* getCStr();

        /// @brief получает путь к прочтённому файлу
        /// @return си-строка, путь
        const char* getPath();
    };
} 

#endif // CODE_HPP
