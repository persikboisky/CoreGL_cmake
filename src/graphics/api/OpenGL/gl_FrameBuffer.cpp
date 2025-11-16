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

		void FrameBuffer::bind() const
		{
			try
			{
				glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
			}
			catch (...)
			{
				throw coders(21, "ID = " + std::to_string(this->fbo));
			}
		}

		void FrameBuffer::unBind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		FrameBuffer::FrameBuffer(const FrameBufferInfo& info)
		{
			glGenFramebuffers(1, &this->fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);

			GLint format;
			if (info.colorsChannels == 1)
				format = GL_RED;
			else if (info.colorsChannels == 3)
				format = GL_RGB;
			else
				format = GL_RGBA;

			glGenTextures(1, &this->texture);
			glBindTexture(GL_TEXTURE_2D, this->texture);
			glTexImage2D(
					GL_TEXTURE_2D,
					0,
					format,
					info.width,
					info.height,
					0,
					format,
					GL_UNSIGNED_BYTE,
					NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture, 0);

			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, info.width, info.height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			// 5. Прикрепляем RBO к FBO в качестве прикрепления глубины и трафарета
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

			// 6. Проверяем, готов ли FBO к использованию
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				throw coders(21, "ID = " + std::to_string(this->fbo));
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		FrameBuffer FrameBuffer::create(const FrameBufferInfo& info)
		{
			return FrameBuffer(info);
		}

		FrameBuffer* FrameBuffer::ptrCreate(const FrameBufferInfo& info)
		{
			return new FrameBuffer(info);
		}

		FrameBuffer::~FrameBuffer()
		{
			if (this->rbo != 0)
				glDeleteRenderbuffers(1, &this->rbo);
			glDeleteFramebuffers(1, &this->fbo);
			glDeleteTextures(1, &this->texture);
		}

		void FrameBuffer::bindTexture(unsigned int sampler)
		{
			glActiveTexture(GL_TEXTURE0 + sampler);
			glBindTexture(GL_TEXTURE_2D, this->texture);
		}
	}
}