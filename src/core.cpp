//
// Created by kisly on 13.07.2025.
//

#include "../include/core.hpp"
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
}

void core::Core::Terminate()
{
    glfwTerminate();
}

double core::Core::getTime()
{
    return glfwGetTime();
}