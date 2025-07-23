//
// Created by kisly on 13.07.2025.
//
#include "fbo.hpp"
#include "texture.hpp"
#include "../../util/coders.hpp"
#include "../../util/types.hpp"
#include <glad/glad.h>

using namespace core;

#pragma region fbo

int fbo::x = 0;
int fbo::y = 0;
int fbo::width = 720;
int fbo::height = 1280;

void fbo::update()
{
    glViewport(fbo::x, fbo::y, fbo::width, fbo::height);
}

void fbo::setSize(int width, int height)
{
    fbo::width = width;
    fbo::height = height;
    fbo::update();
}

void fbo::setSize(const size2i& size)
{
    fbo::setSize(size.width, size.height);
}

void fbo::setPos(int x, int y)
{
    fbo::x = x;
    fbo::y = y;
    fbo::update();
}

void fbo::setPos(const pos2i& pos)
{
    fbo::setPos(pos.x, pos.y);
}

void fbo::setColor(color::RGB color, bool normalize)
{
    if (normalize)
    {
        color.red /= 255.0f;
        color.green /= 255.0f;
        color.blue /= 255.0f;
    }

    glClearColor(
            color.red,
            color.green,
            color.blue,
            1.0f
    );
}

void fbo::setColor(color::RGBA color, bool normalize)
{
    if (normalize)
    {
        color.red /= 255.0f;
        color.green /= 255.0f;
        color.blue /= 255.0f;
        color.alpha /= 255.0f;
    }

    glClearColor(
            color.red,
            color.green,
            color.blue,
            color.alpha
    );
}

void fbo::setColor(float red, float green, float blue, float alpha, bool normilize)
{
    if (normilize)
    {
        red /= 255.0f;
        green /= 255.0f;
        blue /= 255.0f;
        alpha /= 255.0f;
    }

    glClearColor(
            red,
            green,
            blue,
            alpha
    );
}

void fbo::setColor(const color::COLOR& color)
{
    fbo::setColor(color::RGB(color));
}

void fbo::clearBuffers(Buffer buffer1, Buffer buffer2, Buffer buffer3)
{
    Buffer array[3] = { buffer1, buffer2, buffer3 };
    for (unsigned int index = 0; index < 3; index++)
    {
        switch (array[index])
        {
            case COLOR_BUFFER:
                glClear(GL_COLOR_BUFFER_BIT);
                break;

            case DEPTH_BUFFER:
                glClear(GL_DEPTH_BUFFER_BIT);
                break;

            default:
                break;
        }
    }
}

#pragma endregion

#pragma region FBO

void core::FBO::bind()
{
    try
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->idFbo);
    }
    catch (...)
    {
        throw coders(21, "ID = " + std::to_string(this->idFbo));
    }

    this->flagBind = true;
}

void core::FBO::unBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    this->flagBind = false;
}

void core::FBO::bindTexture(unsigned int Sampler)
{
    this->sampler = Sampler;
    texture::bind(this->idTexture, Sampler);
}

void core::FBO::unBindTexture()
{
    texture::bind(0, this->sampler);
}

static inline unsigned int createNULLTexture(int width, int height, int colorsChannels)
{
    unsigned int id;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    int type = (colorsChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (id <= 0) throw coders(23);

    return id;
}

core::FBO::FBO(int width, int height, int colorsChannels) :
    idFbo(0), idRboDepth(0), idRboStencil(0), width(width), height(height), colorChannels(colorsChannels)
{
    glGenFramebuffers(1, &this->idFbo);
    if (this->idFbo <= 0)
    {
        throw coders(22);
    }

    this->bind();

    this->idTexture = createNULLTexture(width, height, colorsChannels);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->idTexture, 0);

    glGenRenderbuffers(1, &this->idRboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, this->idRboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->idRboDepth);

    this->unBind();
}

core::FBO core::FBO::create(int width, int height, int colorsChannels)
{
    return core::FBO(width, height, colorsChannels);
}

core::FBO::~FBO()
{
    texture::Delete(this->idTexture);
    glDeleteFramebuffers(1, &this->idFbo);
    glDeleteRenderbuffers(1, &this->idRboDepth);
}

void core::FBO::resize(int width, int height)
{
    if (this->width == width && this->height == height)
    {
        return;
    }

    this->width = width;
    this->height = height;

    glBindRenderbuffer(GL_RENDERBUFFER, this->idRboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, this->idFbo);
    texture::Delete(this->idTexture);
    this->idTexture = createNULLTexture(width, height, this->colorChannels);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->idTexture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void core::FBO::resize(const size2i& size)
{
    this->resize(size.width, size.height);
}

void core::FBO::fill(const color::RGBA& color)
{
    if (!this->flagBind) this->bind();

    fbo::setColor(color);
    fbo::clearBuffers(COLOR_BUFFER, DEPTH_BUFFER);
}

void core::FBO::fill(const color::RGB& color)
{
    this->fill(color::RGBA(color));
}

void core::FBO::fill(const color::COLOR& color)
{
    this->fill(color::RGBA(color));
}

unsigned int core::FBO::getTextureId()
{
    return this->idTexture;
}

#pragma endregion

