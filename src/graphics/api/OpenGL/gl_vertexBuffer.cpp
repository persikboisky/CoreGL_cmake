//
// Created by kisly on 18.09.2025.
//

#include "gl_vertexBuffer.hpp"
#include "../../../util/coders.hpp"
#include "../../../util/types.hpp"
#include "../../../package/glew-2.1.0/include/GL/glew.h"

namespace core
{
	namespace opengl
	{
		VertexBuffer::VertexBuffer(const VertexBufferInfo& info) :
			type(info.valueType), countElementToVertex(info.countElementToVertex)
		{
			this->sizeOfByte = info.sizeOfByte;

			glGenVertexArrays(1, &this->VAO);
			glGenBuffers(1, &this->VBO);

			if (this->VAO == -1)
			{
				throw coders(13);
			}

			if (VBO == -1)
			{
				throw coders(14);
			}

			this->bind();
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(
					GL_ARRAY_BUFFER,
					info.sizeOfByte,
					info.ptrArray,
					GL_STATIC_DRAW);
			this->unBind();

			switch (info.valueType)
			{
			case INT:
				this->byteToElement = sizeof(GLint);
				break;
			case UNSIGNED_INT:
				this->byteToElement = sizeof(GLuint);
				break;
			case FLOAT:
				this->byteToElement = sizeof(GLfloat);
				break;
			case DOUBLE:
				this->byteToElement = sizeof(GLdouble);
				break;
			}
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteVertexArrays(1, &this->VAO);
			glDeleteBuffers(1, &this->VBO);
		}

		VertexBuffer VertexBuffer::create(const VertexBufferInfo& info)
		{
			return VertexBuffer(info);
		}

		VertexBuffer* VertexBuffer::ptrCreate(const VertexBufferInfo& info)
		{
			return new VertexBuffer(info);
		}

		void VertexBuffer::bind() const
		{
			try
			{
				glBindVertexArray(this->VAO);
			}
			catch (...)
			{
				throw coders(12, "id = " + std::to_string(this->VAO));
			}
		}

		void VertexBuffer::unBind() const
		{
			glBindVertexArray(0);
		}

		void VertexBuffer::addAttribute(unsigned int location, int nElement, int offset) const
		{
			int type = 0;
			switch (this->type)
			{
			case INT:
				type = GL_INT;
				break;
			case UNSIGNED_INT:
				type = GL_UNSIGNED_INT;
				break;
			case FLOAT:
				type = GL_FLOAT;
				break;
			case DOUBLE:
				type = GL_DOUBLE;
				break;
			}

			this->bind();
			try
			{
				glVertexAttribPointer(
						location,
						nElement,
						type,
						GL_FALSE,
						this->countElementToVertex * this->byteToElement,
						(void*)(offset * static_cast<unsigned long long>(this->byteToElement)));
				glEnableVertexAttribArray(location);
				this->unBind();
			}
			catch (...)
			{
				throw coders(15);
			}
			this->unBind();
		}

		unsigned int VertexBuffer::getSizeOfByte() const
		{
			return this->sizeOfByte;
		}

		unsigned int VertexBuffer::getCountVertex() const
		{
			return this->sizeOfByte / this->byteToElement / this->countElementToVertex;
		}


	} // opengl
} // core