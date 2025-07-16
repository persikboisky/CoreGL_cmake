//
// Created by kisly on 13.07.2025.
//

#include "Window.hpp"
#include "Event.hpp"
#include "Cursor.hpp"
#include "Monitor.hpp"
#include "../util/console.hpp"
#include "../util/coders.hpp"
#include "../config.hpp"
#include "../util/types.hpp"
#include "../graphics/commons/fbo.hpp"
#include "../graphics/commons/gl.hpp"
#include "../file/image.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

constexpr int HEIGHT_HEAD_WINDOW = 30;

bool core::Window::flagGladInit = true;

static GLFWwindow *createWindow(int width, int height, const char *title, bool resizable)
{
    glfwWindowHint(GLFW_RESIZABLE, resizable);
    GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window == nullptr)
    {
        throw core::coders(1);
    }

    if (CORE_INFO)
    {
        core::console::printTime();
        std::cout << "Ok: create window" << std::endl;
    }

    return window;
}

void core::Window::getSizeWindow()
{
    glfwGetWindowSize(this->window, &this->width, &this->height);
}

void core::Window::Init()
{
    this->event = new Event(*this->window);
    this->cursor = new Cursor(*this->window);
    this->monitor = new Monitor();
}

core::Window::Window(const core::windowInfo &winInfo) : 
    window(createWindow(winInfo.width, winInfo.height, winInfo.title, winInfo.resizable)),
    event(nullptr), width(winInfo.width), height(winInfo.height), posX(winInfo.posX), posY(winInfo.posY),
    saveWidth(winInfo.width), saveHeight(winInfo.height), cursor(nullptr), monitor(nullptr),
    VSfps(winInfo.VerticalSynchronization), flagFullScreen(winInfo.fullScreen)
{
    this->Init();
    if (winInfo.pathToIcon != nullptr)
    {
        this->setIcon(winInfo.pathToIcon);
    }
    this->fullScreen(winInfo.fullScreen);
}

core::Window::Window(int width, int height, const char *title, bool resizable) : 
    window(createWindow(width, height, title, resizable)), cursor(nullptr), VSfps(true), monitor(nullptr),
    event(nullptr), width(width), height(height), posX(0), posY(0), saveWidth(width), saveHeight(height)
{
    this->Init();
}

void core::Window::setMonitor(core::Monitor monitor)
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

core::Window core::Window::create(const core::windowInfo &winInfo)
{
    return Window(winInfo);
}

core::Window core::Window::create(int width, int height, const char *title, bool resizable)
{
    return Window(width, height, title, resizable);
}

GLFWwindow *core::Window::getWindowOBJ()
{
    return this->window;
}

bool core::Window::isContext()
{
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

static void gladInit()
{
    if (!gladLoadGL())
    {
        throw core::coders(2);
    }

    if (CORE_INFO)
    {
        core::console::printTime();
        std::cout << "Ok: init glad" << std::endl;
        core::console::printTime();
        std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
        core::console::printTime();
        std::cout << "Opengl & Driver : v" << glGetString(GL_VERSION) << std::endl;
    }
}

void core::Window::setContext()
{
    glfwMakeContextCurrent(this->window);

    if (this->flagGladInit)
    {
        gladInit();
        this->flagGladInit = false;
    }

    gl::setDirectFronFace(core::DIRECT_FRONT_FACE{OPENGL_FRONT_FACE});
    gl::enableCullFace(OPENGL_CULL_FACE_FUNCTION);

    if (OPENGL_CULL_FACE_FUNCTION)
    {
        gl::setTypeCullFace(core::TYPE_CULL_FACE{OPENGL_CULL_FACE});
    }
    gl::enableDepthTest(OPENGL_DEPTH_FUNCTION);
}

void core::Window::swapBuffers()
{
    (this->VSfps) ? glfwSwapInterval(1) : glfwSwapInterval(0);
    
    glfwSwapBuffers(this->window);
    this->getSizeWindow();

    if (!this->flagFullScreen) glfwGetWindowPos(this->window, &this->posX, &this->posY);
}

void core::Window::enableZBuffer()
{
    if (!isContext())
    {
        this->setContext();
    }

    if (OPENGL_DEPTH_FUNCTION != true)
        gl::enableDepthTest();
}

void core::Window::setClearColor(const color::RGBA &color)
{
    if (!isContext())
    {
        this->setContext();
    }

    core::fbo::setColor(color);
}

void core::Window::clearFrameBuffer()
{
    if (!isContext())
    {
        this->setContext();
    }

    core::fbo::clearBuffers(COLOR_BUFFER);
}

void core::Window::clearZBuffer()
{
    if (!isContext())
    {
        this->setContext();
    }

    core::fbo::clearBuffers(DEPTH_BUFFER);
}

void core::Window::setSizeFrameBuffer(int width, int height)
{
    if (!isContext())
    {
        this->setContext();
    }

    core::fbo::setSize(width, height);
}

void core::Window::setSizeFrameBuffer(const core::size2i &size)
{
    this->setSizeFrameBuffer(size.width, size.height);
}

void core::Window::setPosFrameBuffer(int x, int y)
{
    if (!this->isContext())
    {
        this->setContext();
    }
    fbo::setPos(x, y);
}

void core::Window::setPosFrameBuffer(const pos2i &pos)
{
    this->setSizeFrameBuffer(pos.x, pos.y);
}

void core::Window::setIcon(const char *pathToImg)
{
    GLFWimage images[1] = {};

    int channels = 0;
    images[0].pixels = core::image::load(pathToImg, images[0].width, images[0].height, channels);

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

core::size2i core::Window::getSize() const
{
    return size2i(this->width, this->height);
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

void core::Window::setPos(const pos2i &pos)
{
    this->setPos(pos.x, pos.y);
}

void core::Window::setPos(const POSITION &pos)
{
    switch (pos)
    {
    case CENTER:
        this->setPos(
            this->monitor->getSize().width / 2 - this->width / 2,
            this->monitor->getSize().height / 2 - this->height / 2 + HEIGHT_HEAD_WINDOW);
        break;

    case UP_CENTER_SIDE:
        this->setPos(
            this->monitor->getSize().width / 2 - this->width / 2,
            HEIGHT_HEAD_WINDOW);
        break;

    case DOWN_CENTER_SIDE:
        this->setPos(
            this->monitor->getSize().width / 2 - this->width / 2,
            this->monitor->getSize().height - HEIGHT_HEAD_WINDOW - this->height);
        break;

    case LEFT_UP_CORNER:
        this->setPos(
            0,
            HEIGHT_HEAD_WINDOW);
        break;

    case LEFT_CENTER_SIDE:
        this->setPos(
            0,
            this->monitor->getSize().height / 2 - this->height / 2 + HEIGHT_HEAD_WINDOW);
        break;

    case LEFT_DOWN_CORNER:
        this->setPos(
            0,
            this->monitor->getSize().height - HEIGHT_HEAD_WINDOW - this->height);
        break;

    case RIGHT_UP_CORNER:
        this->setPos(
            this->monitor->getSize().width - this->width,
            HEIGHT_HEAD_WINDOW);
        break;

    case RIGHT_CENTER_SIDE:
        this->setPos(
            this->monitor->getSize().width - this->width,
            this->monitor->getSize().height / 2 - this->height / 2 + HEIGHT_HEAD_WINDOW);
        break;

    case RIGHT_DOWN_CORNER:
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

void core::Window::setSize(const size2i &size)
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
        this->setPosFrameBuffer(0, 0);
        this->setSizeFrameBuffer(this->width, this->height);
    }
    else
    {
        this->width = this->saveWidth;
        this->height = this->saveHeight;
        this->resetMonitor();
        this->setPos(this->posX, this->posY);
        this->setPosFrameBuffer(0, 0);
        this->setSizeFrameBuffer(this->width, this->height);
    }
}

