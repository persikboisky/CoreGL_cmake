//
// Created by kisly on 14.07.2025.
//

#ifndef CODE_HPP
#define CODE_HPP

#include <string>

namespace core
{
    /// @brief класс для чтения текста из файла
    class Code
    {
    private:
        std::string text;
        std::string path;

        explicit Code(const std::string& path);

    public:
        /// @brief читает файл
        /// @param path путь к файлу
        /// @param flagDebuInfo разрешить выводить информацию в консоль
        /// @return строку текста прочитанную из файла
        static std::string loadStr(const std::string& path, bool flagDebuInfo = true);

        /// @brief читает файл
        /// @param path путь к файлу
        /// @return объект класса code
        static Code load(const std::string& path);

        /// @brief получает прочитанную строку
        /// @return строку
        std::string getStr();

        /// @brief получает прочитанную строку
        /// @return си-строку
        const char* getCStr() const;

        std::string getPath() const;

        /// @brief получает путь к прочтённому файлу
        /// @return си-строка, путь
        const char* getCStrPath() const;
    };
} 

#endif // CODE_HPP
