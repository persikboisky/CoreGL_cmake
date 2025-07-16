//
// Created by kisly on 14.07.2025.
//

#ifndef CODE_HPP
#define CODE_HPP

#include <string>

namespace core
{
    class code
    {
    private:
        std::string text;
        const char* path;

        code(const char* path);

    public:
        static std::string loadStr(const char* path);
        static code load(const char* path);

        std::string getStr();
        const char* getCStr();

        const char* getPath();
    };
} 

#endif // CODE_HPP
