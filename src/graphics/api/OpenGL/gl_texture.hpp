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
		    bool useMipmap = false;
		    bool useUserSampler = false;
		};

		/// @brief класс для создание openGL текстуры
		class Texture
		{
		private:
			unsigned int id;

			explicit Texture(const TextureInfo& info);

		public:
			~Texture();

			static Texture create(const TextureInfo& info);
			static Texture *ptrCreate(const TextureInfo& info);

			void bind(unsigned int unit = 0) const;
			void unBind() const;

			unsigned int getId() const;
		};
	} // opengl
} // core

#endif //GL_TEXTURE_HPP
