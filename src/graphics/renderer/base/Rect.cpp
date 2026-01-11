//
// Created by kisly on 25.12.2025.
//

#include "Rect.hpp"
#include "../../../window/Window.hpp"
#include "RenderWindow.hpp"
#include "../../api/OpenGL/gl_vertexBuffer.hpp"

core::Rect::Rect(const RenderWindow &window) : ptrWindow(window.ptrWindow)
{
}

void core::Rect::updateVAO()
{
    if (!flagUpdateVAO)
        return;
    flagUpdateVAO = false;

    if (!ptrWindow->isGlContext())
        ptrWindow->setGlContext();

    if (ptrVertexBuffer != nullptr)
        delete ptrVertexBuffer;
}

void core::Rect::draw(const color::RGBA &color)
{
}

core::Rect core::Rect::create(const RenderWindow &window)
{
    return Rect(window);
}

core::Rect *core::Rect::ptrCreate(const RenderWindow &window)
{
    return new Rect(window);
}


