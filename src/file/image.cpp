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

unsigned char *core::Image::load(
    const char *path, 
    int &width, 
    int &height, 
    int &channels, 
    bool rotateImg, 
    bool info)
{
    stbi_set_flip_vertically_on_load(rotateImg);
    stbi_uc *image = stbi_load(path, &width, &height, &channels, STBI_default);
    if (image == nullptr)
    {
        throw core::coders(3, "Path: " + std::string(path));
    }

    if (CORE_INFO && info)
    {
        core::console::printTime();
        std::cout << "Ok: load Image to path: " << path << std::endl;
        core::console::printTime();
        std::cout << "Width: " << width << std::endl;
        core::console::printTime();
        std::cout << "Height: " << height << std::endl;
        core::console::printTime();
        std::cout << "Channels: " << channels << std::endl;
    }

    return image;
}

core::Image::Image(const char *path, bool rotateImg, bool info) : path(path), width(0), height(0), channels(0)
{
    this->ptrImageCode = Image::load(path, this->width, this->height, this->channels, rotateImg, info);
}

core::Image core::Image::load(const char *path, bool rotateImg, bool info)
{
    return core::Image(path, rotateImg, info);
}

core::Image *core::Image::ptrLoad(const char* path, bool rotateImg, bool info)
{
    return new core::Image(path, rotateImg, info);
}

void core::Image::free(Image& img)
{
    img.~Image();
}

void core::Image::free(unsigned char *img)
{
    stbi_image_free(img);
}

core::Image::~Image()
{
    core::Image::free(this->ptrImageCode);
}

int core::Image::getChannels() const
{
    return this->channels;
}

int core::Image::getHeight() const
{
    return this->height;
}

int core::Image::getWidth() const
{
    return this->width;
}

const char *core::Image::getPath()
{
    return this->path;
}

unsigned char *core::Image::getImageCode()
{
    return this->ptrImageCode;
}

std::vector<unsigned char> core::Image::getVectorImageCode()
{
    return vector::arrayToVector_uchar(this->getImageCode(), this->height * this->channels * this->width);
}

size_t core::Image::getSize() const
{
    return sizeof(unsigned char) * this->channels;
}
