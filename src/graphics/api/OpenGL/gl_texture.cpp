//
// Created by kisly on 22.09.2025.
//

#include "gl_texture.hpp"
#include "../../../util/coders.hpp"
#include "../../../util/console.hpp"
#include <GL/glew.h>
#include <iostream>

namespace core
{
	namespace opengl
	{
		Texture::Texture(const TextureInfo& info) : sampler(0)
		{
			glGenTextures(1, &this->id);

			if (this->id < 0)
			{
				throw coders(16);
			}

			if (info.debugInfo)
			{
				console::printTime();
				std::cout << "OK: create texture id = " << this->id << std::endl;
			}

			this->bind(0);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			GLint format;
			if (info.channels == 1)
				format = GL_RED;
			else if (info.channels == 3)
				format = GL_RGB;
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

			this->unBind();
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

		void Texture::bind(unsigned int sampler)
		{
			try
			{
				glActiveTexture(GL_TEXTURE0 + sampler);
			}
			catch (...)
			{
				throw coders(18);
			}

			try
			{
				glBindTexture(GL_TEXTURE_2D, this->id);
			}
			catch (...)
			{
				throw coders(17);
			}

			this->sampler = sampler;
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