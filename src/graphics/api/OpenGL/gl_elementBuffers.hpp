//
// Created by kisly on 04.10.2025.
//

#ifndef GL_ELEMENTBUFFERS_HPP
#define GL_ELEMENTBUFFERS_HPP

#include "gl_descriptorContainer.hpp"

namespace core
{
	namespace opengl
	{
		/// @brief буфер индексов
		class ElementBuffer : public FunctionBindContainer
		{
		private:
			ElementBuffer(unsigned int *array, unsigned int sizeOfByte);

			unsigned int countVertex = 0;

		public:
			~ElementBuffer();

			/// @brief создаёт идексный буфер
			/// @param array указатель на массив индексов
			/// @param sizeOfByte размер массива в байтах
			/// @return объект класса opengl::ElementBuffers
			static ElementBuffer create(unsigned int *array, unsigned int sizeOfByte);

			/// @brief создаёт идексный буфер
			/// @param array указатель на массив индексов
			/// @param sizeOfByte размер массива в байтах
			/// @return указатель на объект класса opengl::ElementBuffers
			static ElementBuffer* ptrCreate(unsigned int *array, unsigned int sizeOfByte);

			/// @brief прикрепляет буфер индексов
			void bind() const override;

			/// @brief открепляет буфер индексов
			void unBind() const override;

			unsigned int getCountVertexes() const;
		};
	} // openGL
} // core

#endif //GL_ELEMENTBUFFERS_HPP
