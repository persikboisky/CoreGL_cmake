//
// Created by kisly on 21.10.2025.
//

#ifndef GL_FRAMEBUFFER_HPP
#define GL_FRAMEBUFFER_HPP

#include <vector>

namespace core
{
	namespace opengl
	{
		struct FrameBufferInfo
		{
			int width = 600;
			int height = 600;
			int colorsChannels = 3;
			bool flagCreateDepthBuffer = false;
			bool flagCreateStencilBuffer = false;
		};

		class FrameBuffer
		{
		private:
			unsigned int fbo = 0;
			unsigned int rbo = 0;
			unsigned int texture = 0;

			explicit FrameBuffer(const FrameBufferInfo& info);

		public:
			static FrameBuffer create(const FrameBufferInfo& info);
			static FrameBuffer *ptrCreate(const FrameBufferInfo& info);

			void bind() const;
			void unBind() const;

			~FrameBuffer();

			void bindTexture(unsigned int sampler = 0);
		};
	}
}

#endif //GL_FRAMEBUFFER_HPP
