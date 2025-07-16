//
// Created by kisly on 13.07.2025.
//

#ifndef FBO_HPP
#define FBO_HPP

#include "../../util/types.hpp"

namespace core
{
    class Texture;
    struct fbo
    {
    private:
        static int x;
        static int y;
        static int width;
        static int height;

        static void update();

    public:
        static void setSize(int width, int height);
        static void setSize(const size2i& size);

        static void setPos(int x, int y);
        static void setPos(const pos2i& pos);

        static void setColor(color::RGB color, bool normalize = true);
        static void setColor(color::RGBA color, bool normalize = true);
        static void setColor(float red, float green, float blue, float alpha, bool normalize = true);
        static void setColor(const color::COLOR& color);

        static void clearBuffers(Buffer buffer1, Buffer beffer2 = NONE, Buffer buffer3 = NONE);
    };

    class FBO
    {
    private:
        unsigned int idFbo;
        unsigned int idTexture;
        unsigned int idRboDepth;
        unsigned int idRboStencil;

        unsigned int width;
        unsigned int height;
        unsigned int colorChannels;

        bool flagBind = false;
        unsigned int sampler = 0;

        FBO(int width, int height, int colorsChannels);

    public:
        void bind();
        void unBind();

        void bindTexture(unsigned int Sampler = 0);
        void unBindTexture();

        static FBO create(int width, int height, int colorsChannels = 3);
        ~FBO();

        void resize(int width, int height);
        void resize(const size2i& size);

        void fill(const color::RGBA& color);
        void fill(const color::RGB& color);
        void fill(const color::COLOR& color);
    };
}

#endif //FBO_HPP
