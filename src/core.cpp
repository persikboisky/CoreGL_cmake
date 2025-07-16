//
// Created by kisly on 13.07.2025.
//

#include "../include/core.hpp"
#include "graphics/commons/vao.hpp"
#include "graphics/commons/ebo.hpp"
#include "graphics/commons/shader.hpp"
#include "graphics/commons/texture.hpp"
#include "config.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

void core::Core::Init()
{
    int code = glfwInit();
    if(code == GLFW_FALSE)
    {
        throw core::coders(0);
    }

    if(CORE_INFO)
    {
        int major;
        int minor;
        int rev;
        glfwGetVersion(&major, &minor, &rev);

        core::console::printTime();
        std::cout << "Ok: init GLFW v";
        std::cout << major << "." << minor << "." << rev << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void core::Core::Terminate()
{
    ebo::DeleteALL();
    vao::DeleteALL();
    shader::DeleteALL();
    texture::DeleteALL();
    
    glfwTerminate();
}

double core::Core::getTime()
{
    return glfwGetTime();
}