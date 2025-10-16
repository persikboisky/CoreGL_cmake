//
// Created by kisly on 04.10.2025.
//

#ifndef GL_ELEMENTBUFFERS_HPP
#define GL_ELEMENTBUFFERS_HPP

namespace core
{
	namespace opengl
	{
		/// @brief буфер индексов
		class ElementBuffers
		{
		private:
			unsigned int id;

			ElementBuffers(unsigned int *array, unsigned int sizeOfByte);

		public:
			~ElementBuffers();

			/// @brief создаёт идексный буфер
			/// @param array указатель на массив индексов
			/// @param sizeOfByte размер массива в байтах
			/// @return объект класса opengl::ElementBuffers
			static ElementBuffers create(unsigned int *array, unsigned int sizeOfByte);

			/// @brief создаёт идексный буфер
			/// @param array указатель на массив индексов
			/// @param sizeOfByte размер массива в байтах
			/// @return указатель на объект класса opengl::ElementBuffers
			static ElementBuffers* ptrCreate(unsigned int *array, unsigned int sizeOfByte);

			/// @brief прикрепляет буфер индексов
			void bind() const;

			/// @brief открепляет буфер индексов
			void unBind() const;
		};
	} // openGL
} // core

#endif //GL_ELEMENTBUFFERS_HPP
