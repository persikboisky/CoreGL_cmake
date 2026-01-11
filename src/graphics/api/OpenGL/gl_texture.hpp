//
// Created by kisly on 22.09.2025.
//

#ifndef GL_TEXTURE_HPP
#define GL_TEXTURE_HPP

#include "../../../types/apiTypes.hpp"

namespace core
{
	namespace opengl
	{
		struct TextureCreateInfo
		{
			unsigned int width = 0;
			unsigned int height = 0;

		    bool useMipmap = false;
		    bool useUserSampler = false;

		    const void* data = nullptr;

		    IMAGE_FORMAT format = IMAGE_FORMAT::RGB;
		    IMAGE_INTERNAL_FORMAT internalFormat = IMAGE_INTERNAL_FORMAT::RGB8;
            IMAGE_TYPE type = IMAGE_TYPE::UNSIGNED_BYTE;
		};

		/// @brief класс для создание openGL текстуры
		class Texture
		{
		protected:
		    friend class ShaderProgram;

		private:
			unsigned int id;
		    unsigned int unit;

			explicit Texture(const TextureCreateInfo& info);

		public:
			~Texture();

			static Texture create(const TextureCreateInfo& info);
			static Texture *ptrCreate(const TextureCreateInfo& info);

			void bind(unsigned int unit = 0);
			void unBind();
		};
	} // opengl
} // core

#endif //GL_TEXTURE_HPP
