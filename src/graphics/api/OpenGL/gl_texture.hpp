//
// Created by kisly on 22.09.2025.
//

#ifndef GL_TEXTURE_HPP
#define GL_TEXTURE_HPP

namespace core
{
	namespace opengl
	{
		struct TextureInfo
		{
			unsigned int width = 0;
			unsigned int height = 0;
			unsigned int channels = 0;
			const void* data = nullptr;
			bool debugInfo = false;
		};

		class Texture
		{
		private:
			unsigned int id;
			unsigned int sampler;

			explicit Texture(const TextureInfo& info);

		public:
			~Texture();

			static Texture create(const TextureInfo& info);
			static Texture *ptrCreate(const TextureInfo& info);

			void bind(unsigned int sampler);
			void unBind() const;

			unsigned int getId() const;
		};
	} // opengl
} // core

#endif //GL_TEXTURE_HPP
