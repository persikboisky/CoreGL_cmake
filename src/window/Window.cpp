//
// Created by kisly on 13.07.2025.
//

#include "../modules.hpp"
#include "Window.hpp"
#include "Event.hpp"
#include "Cursor.hpp"
#include "Monitor.hpp"
#include "../util/console.hpp"
#include "../util/coders.hpp"
#include "../config.hpp"
#include "../types/size.hpp"
#include "../types/pos.hpp"
#include "../file/image.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#endif // defined(CORE_INCLUDE_VULKAN)

#define HEIGHT_HEAD_WINDOW 30

bool core::Window::flagGladInit = true;

void core::Window::createWindow(int width, int height, const char *title, bool resizable, bool vkAPI, GLFWmonitor *ptrMon)
{
#if defined(CORE_INCLUDE_VULKAN)
    if (vkAPI)
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    else
#endif // defined(CORE_INCLUDE_VULKAN)
    {
        glfwWindowHint(GLFW_OPENGL_API, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RED_BITS, 8);     // Биты на красный канал
        glfwWindowHint(GLFW_GREEN_BITS, 8);   // Биты на зеленый канал
        glfwWindowHint(GLFW_BLUE_BITS, 8);    // Биты на синий канал
        glfwWindowHint(GLFW_ALPHA_BITS, 8);   // Биты на альфа-канал
        glfwWindowHint(GLFW_DEPTH_BITS, 24);  // Биты буфера глубины
        glfwWindowHint(GLFW_STENCIL_BITS, 8); // Биты буфера трафарета
    }

    glfwWindowHint(GLFW_RESIZABLE, resizable);

    this->window = glfwCreateWindow(width, height, title, ptrMon, nullptr);

    if (this->window == nullptr)
    {
        throw core::coders(1);
    }

    if (CORE_INFO)
    {
        core::console::printTime();
        std::cout << "Ok: create window" << std::endl;
    }
}

void core::Window::getSizeWindow()
{
    glfwGetWindowSize(this->window, &this->width, &this->height);
}

void core::Window::Init()
{
    this->event = new Event(*this->window);
    this->cursor = new Cursor(*this->window);
}

core::Window::Window(const core::WindowInfo &winInfo) : 
    window(nullptr), event(nullptr), width(winInfo.width), height(winInfo.height),
    posX(winInfo.posX), posY(winInfo.posY), saveWidth(winInfo.width), saveHeight(winInfo.height),
    cursor(nullptr), monitor(new Monitor()), flagFullScreen(winInfo.fullScreen),
    time(glfwGetTime()), deltaTime(glfwGetTime())
{
#if defined(CORE_INCLUDE_VULKAN)
    this->VulknanAPI = winInfo.VulkanAPI;
#endif // defined(CORE_INCLUDE_VULKAN)

    GLFWmonitor *ptrMon = nullptr;
    if (winInfo.fullScreen)
        ptrMon = this->monitor->getGLFWObj();
    if (!this->VulknanAPI)
    {
        if (winInfo.ptrApiGlInfo != nullptr)
        {
            this->VSfps = winInfo.ptrApiGlInfo->VerticalSynchronization;
            glfwWindowHint(GLFW_VERSION_MAJOR, winInfo.ptrApiGlInfo->OpenGlVersion.MAJOR);
            glfwWindowHint(GLFW_VERSION_MINOR, winInfo.ptrApiGlInfo->OpenGlVersion.MINOR);
        }
        else
        {
            this->VSfps = true;
            glfwWindowHint(GLFW_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_VERSION_MINOR, 3);
        }
    }

    glfwWindowHint(GLFW_DECORATED, winInfo.windowDecorate);
    glfwWindowHint(GLFW_FOCUSED, winInfo.windowFocus);

    this->createWindow(winInfo.width, winInfo.height, winInfo.title, winInfo.resizable,
#if defined(CORE_INCLUDE_VULKAN)
                       winInfo.VulkanAPI,
#else
                       false,
#endif // defined(CORE_INCLUDE_VULKAN
                       ptrMon);

    this->Init();
    if (winInfo.pathToIcon != nullptr)
    {
        this->setIcon(winInfo.pathToIcon);
    }
}

core::Window::Window(int width, int height, const char *title, bool resizable, bool vkAPI) :
    window(nullptr), cursor(nullptr), VSfps(true), monitor(nullptr),
    event(nullptr), width(width), height(height), posX(0), posY(0), saveWidth(width), saveHeight(height),
    time(glfwGetTime()), deltaTime(glfwGetTime())
{
    GLFWmonitor *ptrMon = nullptr;
    if (!this->VulknanAPI)
    {
        glfwWindowHint(GLFW_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_VERSION_MINOR, 3);
    }
    this->createWindow(width, height, title, resizable, vkAPI, ptrMon);

#if defined(CORE_INCLUDE_VULKAN)
    this->VulknanAPI = vkAPI;
#endif // defined(CORE_INCLUDE_VULKAN)

    this->Init();
}

void core::Window::setMonitor(core::Monitor &monitor)
{
    glfwSetWindowMonitor(
        this->window,
        monitor.getGLFWObj(),
        0, 0,
        monitor.getSize().width,
        monitor.getSize().height,
        GLFW_DONT_CARE);
}

void core::Window::resetMonitor()
{
    glfwSetWindowMonitor(
        this->window,
        nullptr,
        0, 0,
        this->width, this->height,
        GLFW_DONT_CARE);
}

core::Window core::Window::create(const core::WindowInfo &winInfo)
{
    return Window(winInfo);
}

core::Window core::Window::create(int width, int height, const char *title, bool resizable, bool vkAPI)
{
    return Window(width, height, title, resizable, vkAPI);
}

GLFWwindow *core::Window::getWindowOBJ()
{
    return this->window;
}

bool core::Window::isContext()
{
#if defined(CORE_INCLUDE_VULKAN)
    if (this->VulknanAPI)
        return false;
#endif // defined(CORE_INCLUDE_VULKAN)

    if (this->window == glfwGetCurrentContext())
    {
        return true;
    }

    return false;
}

core::Window::~Window()
{
    delete this->event;
    delete this->cursor;
    glfwDestroyWindow(this->window);
}

static inline void glInit()
{
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        throw core::coders(2);
    }

    if (CORE_INFO)
    {
        core::console::printTime();
        std::cout << "=== OpenGL System Information ===" << std::endl;
        core::console::printTime();
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        core::console::printTime();
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
        core::console::printTime();
        std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
        core::console::printTime();
        std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        core::console::printTime();
        int major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        std::cout << "Core Version: " << major << "." << minor << std::endl;
        core::console::printTime();
        if (glewIsSupported("GL_VERSION_4_5"))
        {
            std::cout << "OpenGL 4.5 is supported!" << std::endl;
        }
        core::console::printTime();
        int maxTextureSize;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
        std::cout << "Max Texture Size: " << maxTextureSize << "x" << maxTextureSize << std::endl;
        core::console::printTime();
        int maxVertexAttribs;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
        std::cout << "Max Vertex Attributes: " << maxVertexAttribs << std::endl;
        core::console::printTime();
        std::cout << "=================================" << std::endl;
    }
}

void core::Window::setGlContext()
{
#if defined(CORE_INCLUDE_VULKAN)
    if (!this->VulknanAPI)
    {
#endif // defined(CORE_INCLUDE_VULKAN)
        glfwMakeContextCurrent(this->window);

        if (this->flagGladInit)
        {
            glInit();
            this->flagGladInit = false;
        }
#if defined(CORE_INCLUDE_VULKAN)
    }
#endif // defined(CORE_INCLUDE_VULKAN)
}

void core::Window::swapBuffers()
{
#if defined(CORE_INCLUDE_VULKAN)
    if (!this->VulknanAPI)
    {
#endif // defined(CORE_INCLUDE_VULKAN)
        (this->VSfps) ? glfwSwapInterval(1) : glfwSwapInterval(0);
#if defined(CORE_INCLUDE_VULKAN)
    }
#endif // defined(CORE_INCLUDE_VULKAN)
}

void core::Window::setIcon(const char *pathToImg)
{
    GLFWimage images[1] = {};

    int channels = 0;
    images[0].pixels = core::Image::load(pathToImg, images[0].width, images[0].height, channels, false);

    glfwSetWindowIcon(this->window, 1, images);
    free(images[0].pixels);
}

int core::Window::getWidth() const
{
    return this->width;
}

int core::Window::getHeight() const
{
    return this->height;
}

core::Size2i core::Window::getSize() const
{
    return Size2i(this->width, this->height);
}

float core::Window::getAspect()
{
    return (float)this->getWidth() / (float)this->getHeight();
}

void core::Window::VerticalSynchronization(bool flag)
{
    this->VSfps = flag;
}

void core::Window::setPos(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
    glfwSetWindowPos(this->window, posX, posY);
}

void core::Window::setPos(const Pos2i &pos)
{
    this->setPos(pos.x, pos.y);
}

void core::Window::setPos(const POSITION &pos)
{
    switch (pos)
    {
    case POSITION::CENTER:
        this->setPos(
            this->monitor->getSize().width / 2 - this->width / 2,
            this->monitor->getSize().height / 2 - this->height / 2 + HEIGHT_HEAD_WINDOW);
        break;

    case POSITION::UP_CENTER_SIDE:
        this->setPos(
            this->monitor->getSize().width / 2 - this->width / 2,
            HEIGHT_HEAD_WINDOW);
        break;

    case POSITION::DOWN_CENTER_SIDE:
        this->setPos(
            this->monitor->getSize().width / 2 - this->width / 2,
            this->monitor->getSize().height - HEIGHT_HEAD_WINDOW - this->height);
        break;

    case POSITION::LEFT_UP_CORNER:
        this->setPos(
            0,
            HEIGHT_HEAD_WINDOW);
        break;

    case POSITION::LEFT_CENTER_SIDE:
        this->setPos(
            0,
            this->monitor->getSize().height / 2 - this->height / 2 + HEIGHT_HEAD_WINDOW);
        break;

    case POSITION::LEFT_DOWN_CORNER:
        this->setPos(
            0,
            this->monitor->getSize().height - HEIGHT_HEAD_WINDOW - this->height);
        break;

    case POSITION::RIGHT_UP_CORNER:
        this->setPos(
            this->monitor->getSize().width - this->width,
            HEIGHT_HEAD_WINDOW);
        break;

    case POSITION::RIGHT_CENTER_SIDE:
        this->setPos(
            this->monitor->getSize().width - this->width,
            this->monitor->getSize().height / 2 - this->height / 2 + HEIGHT_HEAD_WINDOW);
        break;

    case POSITION::RIGHT_DOWN_CORNER:
        this->setPos(
            this->monitor->getSize().width - this->width,
            this->monitor->getSize().height - HEIGHT_HEAD_WINDOW - this->height);
        break;
    }
}

void core::Window::setSize(int width, int height)
{
    glfwSetWindowSize(this->window, width, height);
}

void core::Window::setSize(const Size2i &size)
{
    glfwSetWindowSize(this->window, size.width, size.height);
}

void core::Window::fullScreen(bool flag)
{
    this->flagFullScreen = flag;

    if (flag)
    {
        this->saveWidth = this->width;
        this->saveHeight = this->height;
        this->setMonitor(*this->monitor);
    }
    else
    {
        if (this->flagGladInit)
        {
            this->width = this->saveWidth;
            this->height = this->saveHeight;
        }

        this->resetMonitor();

        if (this->flagGladInit)
        {
            this->setPos(this->posX, this->posY);
        }
    }
}

double core::Window::getDeltaTime() const
{
    return this->deltaTime;
}

void core::Window::close()
{
    glfwSetWindowShouldClose(this->window, true);
}

void core::Window::update()
{
    glfwSwapBuffers(this->window);
    this->getSizeWindow();

    if (!this->flagFullScreen)
        glfwGetWindowPos(this->window, &this->posX, &this->posY);

    this->deltaTime = glfwGetTime() - this->time;
    this->time = glfwGetTime();

    this->event->update();
}
