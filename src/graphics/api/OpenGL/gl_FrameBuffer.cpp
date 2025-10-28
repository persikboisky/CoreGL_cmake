//
// Created by kisly on 21.10.2025.
//

#include "gl_FrameBuffer.hpp"
#include "gl_texture.hpp"
#include "../../../util/coders.hpp"
#include "../../../util/types.hpp"
#include "../../../package/glew-2.1.0/include/GL/glew.h"

namespace core
{
	namespace opengl
	{
		static inline unsigned int createNULLTexture(int width, int height, int colorsChannels)
		{
			GLint format;
			unsigned int id;

			if (colorsChannels == 1)
				format = GL_RED;
			else if (colorsChannels == 3)
				format = GL_RGB;
			else
				format = GL_RGBA;

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			if (id <= 0) throw coders(23);

			glBindTexture(GL_TEXTURE_2D, 0);
			return id;
		}

		void FrameBuffer::bind() const
		{
			try
			{
				glBindFramebuffer(GL_FRAMEBUFFER, this->idFbo);
			}
			catch (...)
			{
				throw coders(21, "ID = " + std::to_string(this->idFbo));
			}
		}

		void FrameBuffer::unBind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		FrameBuffer::FrameBuffer(int width, int height, int colorsChannels)
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
		}
	}
}