//
// Created by kisly on 22.09.2025.
//

#include "gl_texture.hpp"
#include "../../../util/Coders.hpp"
#include "../../../util/console.hpp"
#include <GL/glew.h>
#include <format>
#include <iostream>

namespace core
{
	namespace opengl
	{
		Texture::Texture(const TextureInfo& info)
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

			GLint format;
			if (info.channels == 1)
			{
			    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			    format = GL_RED;
			}
			else if (info.channels == 3)
			{
			    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			    format = GL_RGB;
			}
			else
			    format = GL_RGBA;

			glTexImage2D(
					GL_TEXTURE_2D,
					0,
					format,
					info.width,
					info.height,
					0,
					format,
					GL_UNSIGNED_BYTE,
					info.data);

		    if (info.useMipmap)
		        glGenerateMipmap(GL_TEXTURE_2D);

			this->unBind();

		    if (info.debugInfo)
		    {
		        console::printTime();
		        std::cout << std::format(
		            "OK: create texture id = {}, width = {}, height = {}, channels = {}",
		            this->id, info.width, info.height, info.channels) << std::endl;
		    }

		    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &this->id);
		}

		Texture Texture::create(const TextureInfo& info)
		{
			return Texture(info);
		}

		Texture *Texture::ptrCreate(const TextureInfo& info)
		{
			return new Texture(info);
		}

		void Texture::bind(unsigned int unit) const
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
		}

		void Texture::unBind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		unsigned int Texture::getId() const
		{
			return this->id;
		}

	} // opengl
} // core