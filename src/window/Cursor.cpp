//
// Created by kisly on 14.07.2025.
//

#include "Cursor.hpp"
#include "../config.hpp"
#include "../file/image.hpp"
#include "../util/Coders.hpp"
#include "../util/console.hpp"
#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <cstring>
#include <iostream>

core::CustomCursor::CustomCursor(const char* pathToImg, const Window& window, int x, int y) :
    cursor_objs(nullptr), ptrWindow(window.window), ptrImg(new GLFWimage)
{
    int ch;
    unsigned char* codeImg = Image::load(pathToImg, this->ptrImg->width, this->ptrImg->height, ch);
    this->ptrImg->pixels = &codeImg[0];

    this->cursor_objs = glfwCreateCursor(this->ptrImg, x, y);
    if (this->cursor_objs == nullptr)
    {
        throw core::Coders(5);
    }

    if (CORE_INFO)
    {
        core::console::printTime();
        std::cout << "Ok: created cursor" << std::endl;
    }
}

core::CustomCursor::CustomCursor(Image& image, int x, int y, const core::Window& window) :
        cursor_objs(nullptr), ptrWindow(window.window), ptrImg(new GLFWimage)
{
    this->ptrImg->pixels = new unsigned char[image.getSize()];
    memcpy(this->ptrImg->pixels, image.getVectorImageCode().data(), image.getSize());
    ptrImg->height = image.getHeight();
    ptrImg->width = image.getWidth();
    this->cursor_objs = glfwCreateCursor(this->ptrImg, x, y);
    if (this->cursor_objs == nullptr)
    {
        throw core::Coders(5);
    }

    if (CORE_INFO)
    {
        core::console::printTime();
        std::cout << "Ok: created cursor" << std::endl;
    }
}

core::CustomCursor::~CustomCursor()
{
    this->unUse();
    glfwDestroyCursor(this->cursor_objs);
    delete[] this->ptrImg->pixels;
    delete this->ptrImg;
}

void core::CustomCursor::use()
{
    glfwSetCursor(ptrWindow, this->cursor_objs);
}

void core::CustomCursor::unUse()
{
    glfwSetCursor(ptrWindow, nullptr);
}

core::CustomCursor core::CustomCursor::create(const char* pathToImg, int x, int y, const core::Window& window)
{
    return core::CustomCursor(pathToImg, window, 0, 0);
}

core::CustomCursor core::CustomCursor::create(core::Image& image, int x, int y, const core::Window& window)
{
    return core::CustomCursor(image, 0, 0, window);
}

core::Cursor::Cursor(GLFWwindow& addrWindow) : window(&addrWindow)
{}

core::Cursor::Cursor(Window& window) : window(window.getWindowOBJ())
{}

core::Cursor::~Cursor()
{
    glfwSetCursor(this->window, nullptr);
}

void core::Cursor::setCursorMode(int mode)
{
    glfwSetInputMode(this->window, GLFW_CURSOR, mode);
}

void core::Cursor::showCursor(bool flag)
{
    if (!flag) setCursorMode(GLFW_CURSOR_HIDDEN);
    else setCursorMode(GLFW_CURSOR_NORMAL);
}

void core::Cursor::disableCursor(bool flag)
{
    if (flag) setCursorMode(GLFW_CURSOR_DISABLED);
    else setCursorMode(GLFW_CURSOR_NORMAL);
}

void core::Cursor::setPosition(double x, double y)
{
    glfwSetCursorPos(this->window, x, y);
}

double core::Cursor::getCordCursorX()
{
    double x, y;
    glfwGetCursorPos(this->window, &x, &y);
    return x;
}

double core::Cursor::getCordCursorY()
{
    double x, y;
    glfwGetCursorPos(this->window, &x, &y);
    return y;
}

void core::Cursor::getCordCursor(double& x, double& y)
{
    glfwGetCursorPos(this->window, &x, &y);
}
