//
// Created by kisly on 23.07.2025.
//

#include "Rect.hpp"
#include "gResource.hpp"
#include "../../util/types.hpp"
#include "../../graphics/commons/vao.hpp"
#include "../../graphics/commons/ebo.hpp"
#include "../../graphics/commons/texture.hpp"
#include "../../graphics/commons/shader.hpp"
#include "../../window/Window.hpp"
#include <vector>

namespace core
{
    void Rect::createVAO()
    {
        float x = this->x;
        float y = this->y;
        float x2 = x + width;
        float y2 = y - height;

        switch(this->typeCoord)
        {
            case WINDOW_COORD:
                if (this->ptrWindow != nullptr)
                {
                    y2 = y + height;
                    x = x / ((float) ptrWindow->getWidth() / 2.0);
                    y = y / ((float) ptrWindow->getHeight() / 2.0);
                    x2 = x2 / ((float) ptrWindow->getWidth() / 2.0);
                    y2 = y2 / ((float) ptrWindow->getHeight() / 2.0);
                }
                break;

            case POSITIVE_WINDOW_COORD:
                if (this->ptrWindow != nullptr)
                {
                    y2 = y + height;
                    x = x / ((float) ptrWindow->getWidth() / 2.0) - 1.0;
                    y = -(y / ((float) ptrWindow->getHeight() / 2.0) - 1.0);
                    x2 = x2 / ((float) ptrWindow->getWidth() / 2.0) - 1.0;
                    y2 = -(y2 / ((float) ptrWindow->getHeight()  / 2.0) - 1.0);
                }
                break;

            case POSITIVE_RELATIVE_COORD:
                x = (x - 0.5) * 2.0;
                y = (y - 0.5) * 2.0;
                x2 = (x2 - 0.5) * 2.0;
                y2 = (y2 - 0.5) * 2.0;
                break;

            default:
                break;
        }

        std::vector<float> vertexes = {};
        vertexes.push_back(x);
        vertexes.push_back(y);
        vertexes.push_back(this->u);
        vertexes.push_back(this->v);

        vertexes.push_back(x);
        vertexes.push_back(y2);
        vertexes.push_back(this->u);
        vertexes.push_back(this->v - this->tHeight);

        vertexes.push_back(x2);
        vertexes.push_back(y2);
        vertexes.push_back(this->u + this->tWidth);
        vertexes.push_back(this->v - this->tHeight);

        vertexes.push_back(x2);
        vertexes.push_back(y);
        vertexes.push_back(this->u + this->tWidth);
        vertexes.push_back(this->v);

        if(this->objVAO != nullptr)
        {
            delete this->objVAO;
            delete this->objEBO;
        }
        this->objVAO = VAO::ptrCreate(vertexes, 4);
        this->objVAO->addAttribute(0, 2, 0);
        this->objVAO->addAttribute(1, 2, 2);

        vertexes.clear();

        std::vector<unsigned int> indexes{0, 1, 2, 0, 2, 3};
        this->objEBO = new EBO(indexes);
        this->objEBO->linkVAO(*this->objVAO);

        indexes.clear();
    }

    Rect::Rect(const pos2f& pos, const size2f& size, const color::RGBA& color) :
        typeCoord(RELATIVE_COORD), x(pos.x), y(pos.y), width(size.width), height(size.height), color(color),
        idTexture(0)
    {
        if (gResource::rectIdShader <= 0)
        {
            gResource::rectIdShader = gResource::loadShader(0);
        }

        this->createVAO();

        unsigned char* img = new unsigned char[4 * 3];
        for (unsigned int index = 0; index < 4 * 3; index++)
            img[index] = 255;
        this->idTexture = texture::load(img, 2, 2, 3, false);
        delete[] img;
    }

    Rect Rect::create(const pos2f& pos, const size2f& size, const color::RGBA& color)
    {
        return Rect(pos, size, color);
    }

    Rect Rect::create(const pos2f& pos, const size2f& size, const color::RGB& color)
    {
        return Rect(pos, size, color);
    }

    Rect Rect::create(const pos2f& pos, const size2f& size, const color::COLOR& color)
    {
        return Rect(pos, size, color);
    }

    Rect *Rect::ptrCreate(const pos2f& pos, const size2f& size, const color::RGBA& color)
    {
        return new Rect(pos, size, color);
    }

    Rect *Rect::ptrCreate(const pos2f& pos, const size2f& size, const color::RGB& color)
    {
        return new Rect(pos, size, color);
    }

    Rect *Rect::ptrCreate(const pos2f& pos, const size2f& size, const color::COLOR& color)
    {
        return new Rect(pos, size, color);
    }

    Rect::~Rect()
    {
        delete this->objVAO;
        delete this->objEBO;
        texture::Delete(this->idTexture);
    }

    void Rect::draw()
    {
        if (this->flagUbdateVao) this->createVAO();

        texture::bind((this->userTexture == 0) ? this->idTexture : this->userTexture, 0);
        shader::use(gResource::rectIdShader);
        shader::UniformRGBA(this->color, "uColor", true);
        this->objEBO->draw(TRIANGLES, 6);
    }

    void Rect::setPos(const pos2f& pos)
    {
        this->flagUbdateVao = true;
        this->x = pos.x;
        this->y = pos.y;
    }

    void Rect::setPos(float x, float y)
    {
        this->flagUbdateVao = true;
        this->x = x;
        this->y = y;
    }

    void Rect::setSize(const size2f& size)
    {
        this->flagUbdateVao = true;
        this->width = size.width;
        this->height = size.height;
    }

    void Rect::setSize(float width, float height)
    {
        this->flagUbdateVao = true;
        this->width = width;
        this->height = height;
    }

    void Rect::setPosTexture(const pos2f& pos)
    {
        this->flagUbdateVao = true;
        this->u = pos.x;
        this->v = pos.y;
    }

    void Rect::setPosTexture(float x, float y)
    {
        this->flagUbdateVao = true;
        this->u = x;
        this->v = y;
    }

    void Rect::setSizeTexture(const size2f& size)
    {
        this->flagUbdateVao = true;
        this->tWidth = size.width;
        this->tHeight = size.height;
    }

    void Rect::setSizeTexture(float width, float height)
    {
        this->flagUbdateVao = true;
        this->tWidth = width;
        this->tHeight = height;
    }

    void Rect::setTexture(unsigned int id)
    {
        this->flagUbdateVao = true;
        this->userTexture = id;
    }

    void Rect::setTexture(const Texture& texture)
    {
        this->flagUbdateVao = true;
        this->userTexture = texture.getID();
    }

    void Rect::disableTexture()
    {
        this->flagUbdateVao = true;
        this->u = 0;
        this->v = 0;
        this->tWidth = 1;
        this->tHeight = 1;
        this->userTexture = 0;
    }

    void Rect::setTypeCoord(const TYPES_COORD& typeCoord)
    {
        this->flagUbdateVao = true;
        this->typeCoord = typeCoord;
    }

    void Rect::setWindow(Window& window)
    {
        this->flagUbdateVao = true;
        this->ptrWindow = &window;
    }

} // core
