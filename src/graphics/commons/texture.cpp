//
// Created by kisly on 14.07.2025.
//

#include "texture.hpp"
#include "../../config.hpp"
#include "../../util/vector.hpp"
#include "../../file/image.hpp"
#include "../../util/coders.hpp"
#include "../../util/console.hpp"
#include "../../util/types.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <functional>

using namespace core;

#pragma region texture
std::vector<unsigned int> texture::id;

void texture::bind(unsigned int id, unsigned int Sample)
{
    try 
    {
        glActiveTexture(GL_TEXTURE0 + Sample);
    }
    catch (...)
    {
        throw coders(18);
    }

    try
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }
    catch (...)
    {
        throw coders(17);
    }
}

unsigned int texture::load(unsigned char *image, int width, int height, int channels, bool info)
{
    // glActiveTexture(GL_TEXTURE0);
    GLuint Texture;
    glGenTextures(1, &Texture);

    if (Texture < 0)
    {
        throw coders(16);
    }
    
    texture::id.push_back(Texture);
    if (CORE_INFO && info)
    {
        console::printTime();
        std::cout << "OK: create texture id = " << Texture << std::endl;
    }

    bind(Texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    switch (channels)
    {
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            break;
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //(GL_LINEAR, GL_NEAREST)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //(GL_LINEAR, GL_NEAREST)

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    bind(0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return Texture;
}

unsigned int texture::load(std::vector<unsigned char> &png_code, int width, int height, int channels, bool info)
{
    return texture::load(png_code.data(), width, height, channels, info);
}

unsigned int texture::load(const char *path, bool info)
{
    int t_width;
    int t_height;
    int t_channels;

    unsigned char *text = image::load(path, t_width, t_height, t_channels, info);
    unsigned int texture_id = load(text, t_width, t_height, t_channels, info);

    image::free(text);

    return texture_id;
}

unsigned int texture::load(image& img, bool info)
{
    std::vector<unsigned char> code = img.getVectorImageCode();
    return texture::load(code, img.getWidth(), img.getHeight(), img.getChannels(), info);
}

void texture::setTypeWrapping(unsigned int textID, const TYPE_WRAPPING_TEXTURE& twt)
{
    std::function<int(TYPE_WRAPPING_TEXTURE)> convertType = [](TYPE_WRAPPING_TEXTURE value){
        switch (value)
        {
            case core::TEXTURE_REPEAT: return GL_REPEAT;
            case core::TEXTURE_MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
            case core::TEXTURE_CLAMP_TO_BORDER : return GL_CLAMP_TO_BORDER;
            case core::TEXTURE_CLAMP_TP_EDGE : return GL_CLAMP_TO_EDGE;
            default : return 0;
        }
    };

    int type = convertType(twt);

    texture::bind(textID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);
    texture::bind(0);
}

void texture::Delete(unsigned int id)
{
    unsigned int index = vector::searchIndexFromValue(texture::id, id);

    if (index != -1)
    {
        glDeleteTextures(1, &id);
        std::vector<unsigned int>::const_iterator iter = texture::id.cbegin();
        texture::id.erase(iter + index);
    }
}

void texture::DeleteALL()
{
    for (int i = 0; i < id.size(); i++)
    {
        glDeleteTextures(1, &id[i]);
        // id[i] = 0;
    }
    id.clear();
}
#pragma endregion texture

#pragma region Texture
Texture::Texture(unsigned char *png_code, int width, int height, int channels)
{
    this->id = texture::load(png_code, width, height, channels);
}

Texture::Texture(std::vector<unsigned char> &png_code, int width, int height, int channels)
{
    this->id = texture::load(png_code.data(), width, height, channels);
}

Texture::Texture(const char *path)
{
    this->id = texture::load(path);
}

Texture::Texture(image& img)
{
    this->id = texture::load(img);
}

Texture::Texture(unsigned int id)
{
    this->id = id;
}

Texture Texture::create(unsigned char* png_code, int width, int height, int channels)
{
    return Texture(png_code, width, height, channels);
}

Texture Texture::create(std::vector<unsigned char>& png_code, int width, int height, int channels)
{
    return Texture(png_code, width, height, channels);
}

Texture Texture::create(image& img)
{
    return Texture(img);
}

Texture *Texture::ptrCreate(unsigned char* png_code, int width, int height, int channels)
{
    return new Texture(png_code, width, height, channels);
}

Texture Texture::load(const char* path)
{
    return Texture(path);
}

Texture Texture::add(unsigned int id)
{
    return Texture(id);
}

Texture::~Texture()
{
    texture::Delete(this->id);
}

void Texture::bind(unsigned int Sample) const
{
    texture::bind(this->id, Sample);
}

void Texture::setTypeWrapping(unsigned int textID, const TYPE_WRAPPING_TEXTURE& twt)
{
    texture::setTypeWrapping(this->id, twt);
}

unsigned int Texture::getID() const
{
    return this->id;
}

#pragma endregion Texture
