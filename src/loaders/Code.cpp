//
// Created by kisly on 14.07.2025.
//

#include "Code.hpp"
#include "../config.hpp"
#include "../util/Coders.hpp"
#include "../util/console.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

core::Code::Code(const std::string& path) : path(path)
{
    this->text = core::Code::loadStr(path);
}

std::string core::Code::loadStr(const std::string& path, bool flagDebuInfo)
{
    std::string text;
    std::ifstream file(path, std::ios::in);
    if (!file.is_open())
        throw Coders(CODE_FAILED_OPEN_FILE, path);

    std::stringstream sstr;
    sstr << file.rdbuf();
    text = sstr.str();
    file.close();

    if (CORE_INFO && flagDebuInfo)
    {
        console::printTime();
        std::cout << "Ok: read file: " << path << std::endl;
    }

    return text;
}

core::Code core::Code::load(const std::string& path)
{
    return core::Code(path);
}

std::string core::Code::getStr()
{
    return this->text;
}

const char* core::Code::getCStr() const
{
    return this->text.c_str();
}

std::string core::Code::getPath() const
{
    return this->path;
}

const char* core::Code::getCStrPath() const
{
    return this->path.c_str();
}


