//
// Created by kisly on 21.10.2025.
//

#ifndef GL_FRAMEBUFFER_HPP
#define GL_FRAMEBUFFER_HPP

namespace core
{
	namespace opengl
	{
		class FrameBuffer
		{
		private:
			unsigned int idFbo;
			unsigned int idTexture;
			unsigned int idRboDepth;

			void bind() const;
			void unBind() const;

			FrameBuffer(int width, int height, int colorsChannels);
		};
	}
}

#endif //GL_FRAMEBUFFER_HPP
