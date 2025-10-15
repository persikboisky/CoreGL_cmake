#include "gl_elementBuffers.hpp"
//
// Created by kisly on 04.10.2025.
//

#include "gl_elementBuffers.hpp"
#include "../../../util/coders.hpp"
#include "../../../package/glew-2.1.0-master/include/GL/glew.h"

namespace core
{
	namespace opengl
	{
		ElementBuffers::ElementBuffers(unsigned int* array, unsigned int sizeOfByte) : id(0)
		{
			glGenBuffers(1, &this->id);
			if (this->id <= 0)
			{
				throw coders(20);
			}

			this->bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfByte, array, GL_STATIC_DRAW);
			this->unBind();
		}

		ElementBuffers::~ElementBuffers()
		{
			glDeleteBuffers(1, &this->id);
		}

		ElementBuffers ElementBuffers::create(unsigned int* array, unsigned int sizeOfByte)
		{
			return ElementBuffers(array, sizeOfByte);
		}

		ElementBuffers* ElementBuffers::ptrCreate(unsigned int* array, unsigned int sizeOfByte)
		{
			return new ElementBuffers(array, sizeOfByte);
		}

		void ElementBuffers::bind() const
		{
			try
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
			}
			catch (...)
			{
				throw coders(19);
			}
		}

		void ElementBuffers::unBind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	} // openGL
} // core