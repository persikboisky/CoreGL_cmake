//
// Created by kisly on 22.09.2025.
//

#include "gl_texture.hpp"
#include "../../../util/Coders.hpp"
#include "../../../util/console.hpp"
#include "../../../config.hpp"
#include <GL/glew.h>
#include <format>
#include <iostream>

namespace core
{
	namespace opengl
	{
		Texture::Texture(const TextureCreateInfo& info) : id(0), unit(0)
		{
		    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glGenTextures(1, &this->id);

			if (this->id < 0)
			{
				throw Coders(16);
			}

			this->bind(0);

		    if (!info.useUserSampler)
		    {
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		    }

			glTexImage2D(
					GL_TEXTURE_2D,
					0,
					Convert::convertAndAlignment(info.internalFormat),
					static_cast<int>(info.width),
					static_cast<int>(info.height),
					0,
					Convert::convert(info.format),
					info.type == IMAGE_TYPE::UNSIGNED_BYTE ? GL_UNSIGNED_BYTE : GL_FLOAT,
					info.data);

		    GLenum error = glGetError();
		    if (error != GL_NO_ERROR)
		    {
		        const char* errorStr = nullptr;
		            switch(error)
		            {
		            case GL_INVALID_ENUM:      errorStr = "(GL_INVALID_ENUM)"; break;
		            case GL_INVALID_VALUE:     errorStr = "(GL_INVALID_VALUE)"; break;
		            case GL_INVALID_OPERATION: errorStr = "(GL_INVALID_OPERATION)"; break;
		            case GL_OUT_OF_MEMORY:     errorStr = "(GL_OUT_OF_MEMORY)"; break;
		            default:                   break;
		            }

		        throw Coders(NONE_CODERS,
		            std::format("Error[core::opengl::Texture]: {}", error));
		    }

		    if (info.useMipmap)
		        glGenerateMipmap(GL_TEXTURE_2D);

			this->unBind();

		    if (CORE_INFO)
		    {
		        console::printTime();
		        std::cout << std::format(
		            "OK: create texture id = {}, width = {}, height = {}",
		            this->id, info.width, info.height) << std::endl;
		    }
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &this->id);
		}

		Texture Texture::create(const TextureCreateInfo& info)
		{
			return Texture(info);
		}

		Texture *Texture::ptrCreate(const TextureCreateInfo& info)
		{
			return new Texture(info);
		}

		void Texture::bind(unsigned int unit)
		{
			try
			{
				glActiveTexture(GL_TEXTURE0 + unit);
			}
			catch (...)
			{
				throw Coders(18);
			}

			try
			{
				glBindTexture(GL_TEXTURE_2D, this->id);
			}
			catch (...)
			{
				throw Coders(17);
			}

		    this->unit = unit;
		}

		void Texture::unBind()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		    unit = 0;
		}
	} // opengl
} // core