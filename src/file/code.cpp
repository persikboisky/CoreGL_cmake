//
// Created by kisly on 14.07.2025.
//

#include "code.hpp"
#include "../config.hpp"
#include "../util/coders.hpp"
#include "../util/console.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

core::code::code(const char *path) : path(path)
{
    this->text = core::code::loadStr(path);
}

std::string core::code::loadStr(const char *path, bool flagDebuInfo)
{
    std::string text = "";
    std::ifstream file(path, std::ios::in);
    if (file.is_open())
    {
        std::stringstream sstr;
        sstr << file.rdbuf();
        text = sstr.str();
        file.close();
    }
    else
    {
        throw core::coders(6, path);
    }

    if (CORE_INFO && flagDebuInfo)
    {
        console::printTime();
        std::cout << "Ok: read file: " << path << std::endl;
    }

    return text;
}

core::code core::code::load(const char *path)
{
    return core::code(path);
}

std::string core::code::getStr()
{
    return this->text;
}

const char* core::code::getCStr()
{
    return this->text.c_str();
}

const char* core::code::getPath()
{
    return this->path;
}




