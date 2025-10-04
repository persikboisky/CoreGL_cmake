//
// Created by kisly on 04.10.2025.
//

#ifndef GL_ELEMENTBUFFERS_HPP
#define GL_ELEMENTBUFFERS_HPP

namespace core
{
	namespace openGL
	{
		class ElementBuffers
		{
		private:
			unsigned int id;

			ElementBuffers(unsigned int *array, unsigned int sizeOfByte);

		public:
			static ElementBuffers create(unsigned int *array, unsigned int sizeOfByte);
			static ElementBuffers* ptrCreate(unsigned int *array, unsigned int sizeOfByte);

			void bind();
			void unBind();
		};
	} // openGL
} // core

#endif //GL_ELEMENTBUFFERS_HPP
