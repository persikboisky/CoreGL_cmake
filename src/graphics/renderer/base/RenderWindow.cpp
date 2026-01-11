//
// Created by kisly on 25.12.2025.
//

#include "RenderWindow.hpp"
#include "../../../window/Window.hpp"
#include <GL/glew.h>
#include <string>

namespace core
{
    RenderWindow::RenderWindow(const RenderWindowCreateInfo &info)
    {
        WindowApiGlInfo glInfo;
        glInfo.OpenGlVersion = {3, 3};
        glInfo.VerticalSynchronization = info.vsync;

        WindowCreateInfo windowCreateInfo = {};
        windowCreateInfo.height = info.height;
        windowCreateInfo.width = info.width;
        windowCreateInfo.resizable = info.resizable;
        windowCreateInfo.ptrApiGlInfo = &glInfo;
        windowCreateInfo.title = info.title;

        ptrWindow = Window::ptrCreate(windowCreateInfo);
        ptrWindow->setGlContext();

        event = ptrWindow->event;

        std::string vertCode =
            "#version 330 core\n"
            "layout(location = 0) in vec2 aPos;\n"
            "layout(location = 1) in vec2 aTexCoords;\n"
            "out vec2 TexCoords;\n"
            "uniform mat4 model = mat4(1.0);\n"
            "void main(){\n"
            "   TexCoords = aTexCoords;\n"
            "   gl_Position = model * vec4(aPos, 0.0, 1.0);\n"
            "}";

        std::string fragCode =
            "#version 330 core\n"
            "out vec4 fragColor;\n"
            "in vec2 TexCoords;\n"
            "uniform sampler2D sampler;\n"
            "uniform vec3 color = vec3(1);\n"
            "uniform int flagTexture = 0;\n"
            "void main(){\n"
            "if (flagTexture > 0)\n"
            "   fragColor = texture(sampler, sTexCoords);\n"
            "else\n"
            "   fragColor = color;\n"
            "}";
    }

    RenderWindow RenderWindow::create(const RenderWindowCreateInfo &info)
    {
        return RenderWindow(info);
    }

    RenderWindow *RenderWindow::ptrCreate(const RenderWindowCreateInfo &info)
    {
        return new RenderWindow(info);
    }

    RenderWindow::~RenderWindow()
    {
        delete ptrWindow;
    }

    void RenderWindow::display() const
    {
        if (!ptrWindow->isGlContext())
            ptrWindow->setGlContext();
        ptrWindow->swapBuffers();
    }

    void RenderWindow::clear() const
    {
        if (!ptrWindow->isGlContext())
            ptrWindow->setGlContext();
        glClear(GL_COLOR_BUFFER_BIT);
    }

    } // namespace core