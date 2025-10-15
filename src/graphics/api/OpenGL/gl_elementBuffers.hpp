//
// Created by kisly on 04.10.2025.
//

#ifndef GL_ELEMENTBUFFERS_HPP
#define GL_ELEMENTBUFFERS_HPP

namespace core
{
	namespace opengl
	{
		class ElementBuffers
		{
		private:
			unsigned int id;

			ElementBuffers(unsigned int *array, unsigned int sizeOfByte);

		public:
			~ElementBuffers();

			static ElementBuffers create(unsigned int *array, unsigned int sizeOfByte);
			static ElementBuffers* ptrCreate(unsigned int *array, unsigned int sizeOfByte);

			void bind() const;
			void unBind();
		};
	} // openGL
} // core

#endif //GL_ELEMENTBUFFERS_HPP
