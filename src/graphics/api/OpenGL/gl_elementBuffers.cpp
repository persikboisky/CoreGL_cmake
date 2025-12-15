//
// Created by kisly on 04.10.2025.
//

#include "gl_elementBuffers.hpp"
#include "../../../util/Coders.hpp"
#include <GL/glew.h>

namespace core
{
	namespace opengl
	{
		ElementBuffer::ElementBuffer(unsigned int* array, unsigned int sizeOfByte) : countVertex(sizeOfByte / sizeof(unsigned int))
		{
			glGenBuffers(1, &this->id);
			if (this->id <= 0)
			{
				throw Coders(20);
			}

			this->bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfByte, array, GL_STATIC_DRAW);
			this->unBind();
		}

		ElementBuffer::~ElementBuffer()
		{
			glDeleteBuffers(1, &this->id);
		}

		ElementBuffer ElementBuffer::create(unsigned int* array, unsigned int sizeOfByte)
		{
			return ElementBuffer(array, sizeOfByte);
		}

		ElementBuffer* ElementBuffer::ptrCreate(unsigned int* array, unsigned int sizeOfByte)
		{
			return new ElementBuffer(array, sizeOfByte);
		}

		void ElementBuffer::bind() const
		{
			try
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
			}
			catch (...)
			{
				throw Coders(19);
			}
		}

		void ElementBuffer::unBind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		unsigned int ElementBuffer::getCountVertexes() const
		{
			return this->countVertex;
		}
	} // openGL
} // core