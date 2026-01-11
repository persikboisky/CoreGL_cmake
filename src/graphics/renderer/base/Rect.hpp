//
// Created by kisly on 25.12.2025.
//

#ifndef RECT_HPP
#define RECT_HPP

#include "../../../types/color.hpp"
#include "../../../types/size.hpp"
#include "../../../types/pos.hpp"

namespace core
{
    class Window;
    class RenderWindow;
    namespace opengl
    {
        class VertexBuffer;
    }

    class Rect
    {
    private:
        Window* ptrWindow = nullptr;
        opengl::VertexBuffer* ptrVertexBuffer = nullptr;
        bool flagUpdateVAO = true;

        Rect(const RenderWindow& window);

        void updateVAO();

    public:
        static Rect create(const RenderWindow& window);
        static Rect* ptrCreate(const RenderWindow& window);

        void draw(const color::RGBA& color);
    };
}

#endif // RECT_HPP
