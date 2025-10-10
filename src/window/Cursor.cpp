//
// Created by kisly on 14.07.2025.
//

#include "Cursor.hpp"
#include "Window.hpp"
#include "../file/image.hpp"
#include "../util/coders.hpp"
#include "../util/console.hpp"
#include "../config.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

core::CustomCursor::CustomCursor(const char* pathToImg, int x, int y, GLFWwindow* window) :
    cursor_objs(nullptr), addrWindow(*window), ptrImg(new GLFWimage)
{
    int ch;
    unsigned char* codeImg = Image::load(pathToImg, this->ptrImg->width, this->ptrImg->height, ch);
    this->ptrImg->pixels = this->ptrImg->pixels = &codeImg[0];

    this->cursor_objs = glfwCreateCursor(this->ptrImg, x, y);
    if (this->cursor_objs == nullptr)
    {
        throw core::coders(5);
    }

    if (CORE_INFO)
    {
        core::console::printTime();
        std::cout << "Ok: created cursor > " << pathToImg << std::endl;
    }
}

core::CustomCursor::~CustomCursor()
{
    this->unUse();
    glfwDestroyCursor(this->cursor_objs);
    delete this->ptrImg;
}

void core::CustomCursor::use()
{
    glfwSetCursor(&this->addrWindow, this->cursor_objs);
}

void core::CustomCursor::unUse()
{
    glfwSetCursor(&this->addrWindow, nullptr);
}

core::Cursor::Cursor(GLFWwindow& addrWindow) : window(&addrWindow)
{
}

core::Cursor::Cursor(Window& window) : window(window.getWindowOBJ())
{
}

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

core::CustomCursor core::Cursor::create(const char* pathToPng, int posXimg, int posYimg)
{
    return core::CustomCursor(pathToPng, posXimg, posYimg, this->window);
}

