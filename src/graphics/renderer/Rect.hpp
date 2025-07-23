//
// Created by kisly on 23.07.2025.
//

#ifndef DEVELOPMENTGAMECORE_RECT_HPP
#define DEVELOPMENTGAMECORE_RECT_HPP

#include "../../util/types.hpp"

namespace core
{
    class VAO;
    class EBO;
    class Texture;
    class Window;

    class Rect
    {
    private:
        TYPES_COORD typeCoord;

        float x;
        float y;
        float width;
        float height;

        float u = 0;
        float v = 1;
        float tWidth = 1;
        float tHeight = 1;

        VAO* objVAO = nullptr;
        EBO* objEBO = nullptr;

        unsigned int idTexture;
        unsigned int userTexture = 0;

        color::RGBA color;

        bool flagUbdateVao = false;

        void createVAO();
        Rect(const pos2f& pos, const size2f& size, const color::RGBA& color);

        Window* ptrWindow = nullptr;

    public:
        static Rect create(const pos2f& pos, const size2f& size, const color::RGBA& color);
        static Rect create(const pos2f& pos, const size2f& size, const color::RGB& color);
        static Rect create(const pos2f& pos, const size2f& size, const color::COLOR& color);

        static Rect *ptrCreate(const pos2f& pos, const size2f& size, const color::RGBA& color);
        static Rect *ptrCreate(const pos2f& pos, const size2f& size, const color::RGB& color);
        static Rect *ptrCreate(const pos2f& pos, const size2f& size, const color::COLOR& color);

        ~Rect();

        void draw();

        void setPos(const pos2f& pos);
        void setPos(float x, float y);

        void setSize(const size2f& size);
        void setSize(float width, float height);

        void setPosTexture(const pos2f& pos);
        void setPosTexture(float x, float y);

        void setSizeTexture(const size2f& size);
        void setSizeTexture(float width, float height);

        void setTexture(unsigned int id);
        void setTexture(const Texture& texture);
        void disableTexture();

        void setTypeCoord(const TYPES_COORD& typeCoord);
        void setWindow(Window& window);
    };
} // core

#endif //DEVELOPMENTGAMECORE_RECT_HPP
