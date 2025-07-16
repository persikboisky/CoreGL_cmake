//
// Created by kisly on 13.07.2025.
//

#include "coders.hpp"
#include "console.hpp"
#include <string>
#include <iostream>

const std::string INFO_CODERS[] = {
        "FAILED_INIT_GLFW",
        "FAILED_INIT_WINDOW",
        "FAILED_INIT_GLAD",
        "FAILED_LOAD_IMAGE",
        "FAILED_CHECK_KEY",
        "FAILED_CREATE_CUSTOM_CURSOR",
        "FAILED_LOAD_FILE",
        "FAILED_CREATE_VERTEX_SHADER",
        "FAILED_CREATE_FRAGMENT_SHADER",
        "FAILED_CREATE_SHADER_PROGRAM",
        "FAILED_CREATE_GEOMETRY_SHADER",
        "FAILED_LOCATE_UNIFORM_VARIABLE",
        "FAILED_BIND_VAO",
        "FAILED_CREATE_VAO",
        "FAILED_CREATE_VBO_FOR_VAO",
        "FAILED_ADD_ATTRIBUTE_TO_VAO",
        "FAILED_CREATE_TEXTURE",
        "FAILED_BIND_TEXTURE",
        "FAILED_SET_SAMPLER_TEXTURE_ON_BIND",
        "FAILED_BIND_EBO",
        "FAILED_CREATE_EBO",
        "FAILED_BIND_FBO",
        "FAILED_CREATE_FBO",
        "FAILED_CREATE_TEXTURE_ON_FBO"
};

core::coders::coders(int codeError, std::string addInfo)
{
    this->code = codeError;
    this->info = addInfo;
}

int core::coders::getCode() const
{
    return this->code;
}

std::string core::coders::getInfo()
{
    return {
        INFO_CODERS[this->code] +
        "\n" +
        this->info
    };
}

void core::coders::print()
{
    console::printTime();
    std::cout << "code: " << this->getCode() << std::endl;
    console::printTime();
    std::cout << this->getInfo() << std::endl;
}