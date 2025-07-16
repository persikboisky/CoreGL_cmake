//
// Created by kisly on 13.07.2025.
//

#include "image.hpp"
#include "../util/coders.hpp"
#include "../config.hpp"
#include "../util/console.hpp"
#include "../util/vector.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <string>
#include <iostream>
#include <vector>

unsigned char *core::image::load(const char *path, int &width, int &height, int &channels, bool rotateImg, bool info)
{
    stbi_set_flip_vertically_on_load(rotateImg);
    stbi_uc *image = stbi_load(path, &width, &height, &channels, STBI_default);
    if (image == 0)
    {
        throw core::coders(3, "Path: " + std::string(path));
    }

    if (CORE_INFO && info)
    {
        core::console::printTime();
        std::cout << "Ok: load png to path: " << path << std::endl;
    }

    return image;
}

core::image::image(const char *path, bool rotateImg, bool info) : path(path), width(0), height(0), channels(0)
{
    this->imageCode = image::load(path, this->width, this->height, this->channels, rotateImg, info);
}

core::image core::image::load(const char *path, bool rotateImg, bool info)
{
    return core::image(path, rotateImg, info);
}

void core::image::free(image& image)
{
    image.~image();
}

void core::image::free(unsigned char *img)
{
    stbi_image_free(img);
}

core::image::~image()
{
    core::image::free(this->imageCode);
}

int core::image::getChannels() const
{
    return this->channels;
}

int core::image::getHeight() const
{
    return this->height;
}

int core::image::getWidth() const
{
    return this->width;
}

const char *core::image::getPath()
{
    return this->path;
}

unsigned char *core::image::getImageCode()
{
    return this->imageCode;
}

std::vector<unsigned char> core::image::getVectorImageCode()
{
    return vector::arrayToVector_uchar(this->getImageCode(), this->height * this->channels * this->width);
}
