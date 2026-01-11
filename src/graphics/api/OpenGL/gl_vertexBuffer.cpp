//
// Created by kisly on 18.09.2025.
//

#include "gl_vertexBuffer.hpp"
#include "../../../types/apiTypes.hpp"
#include "../../../util/Coders.hpp"
#include "../../../loaders/models/m_OBJ.hpp"
#include "../../../loaders/models/m_FBX.hpp"
#include <GL/glew.h>
#include <vector>

namespace core
{
	namespace opengl
	{
		VertexBuffer::VertexBuffer(const VertexBufferCreateInfo& info) :
			type(info.valueType), countElementToVertex(info.countElementToVertex)
		{
			this->sizeOfByte = info.sizeOfByte;

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			if (VAO == -1)
			{
				throw Coders(CODE_FAILED_CREATE_VAO);
			}

			if (VBO == -1)
			{
				throw Coders(CODE_FAILED_CREATE_VBO);
			}

			this->bind();
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(
					GL_ARRAY_BUFFER,
					info.sizeOfByte,
					info.ptrArray,
					GL_STATIC_DRAW);
			this->unBind();

            byteToElement = Convert::convertSizeType(info.valueType);
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteVertexArrays(1, &this->VAO);
			glDeleteBuffers(1, &this->VBO);
		}

		VertexBuffer VertexBuffer::create(const VertexBufferCreateInfo& info)
		{
			return VertexBuffer(info);
		}

		VertexBuffer* VertexBuffer::ptrCreate(const VertexBufferCreateInfo& info)
		{
			return new VertexBuffer(info);
		}

        VertexBuffer VertexBuffer::create(const model::OBJ &obj, unsigned int indexMesh)
        {
		    VertexBufferCreateInfo info = {};
		    info.valueType = TYPE::FLOAT;
		    info.ptrArray = obj.meshes[indexMesh].vertices.data();
		    info.countElementToVertex = 8;
            info.sizeOfByte = obj.meshes[indexMesh].vertices.size() * sizeof(obj.meshes[indexMesh].vertices[0]);
		    return VertexBuffer(info);
        }

        VertexBuffer *VertexBuffer::ptrCreate(const model::OBJ &obj, unsigned int indexMesh)
        {
		    VertexBufferCreateInfo info = {};
		    info.valueType = TYPE::FLOAT;
		    info.ptrArray = obj.meshes[indexMesh].vertices.data();
		    info.countElementToVertex = 8;
		    info.sizeOfByte = obj.meshes[indexMesh].vertices.size() * sizeof(obj.meshes[indexMesh].vertices[0]);
		    return new VertexBuffer(info);
        }

        VertexBuffer VertexBuffer::create(const model::FBX &fbx, unsigned int indexMesh)
        {
		    VertexBufferCreateInfo info = {};
		    info.valueType = TYPE::FLOAT;
		    info.ptrArray = fbx.meshes[indexMesh].vertices.data();
		    info.countElementToVertex = 8;
		    info.sizeOfByte = fbx.meshes[indexMesh].vertices.size() * sizeof(fbx.meshes[indexMesh].vertices[0]);
		    return VertexBuffer(info);
        }

        VertexBuffer *VertexBuffer::ptrCreate(const model::FBX &fbx, unsigned int indexMesh)
        {
		    VertexBufferCreateInfo info = {};
		    info.valueType = TYPE::FLOAT;
		    info.ptrArray = fbx.meshes[indexMesh].vertices.data();
		    info.countElementToVertex = 8;
		    info.sizeOfByte = fbx.meshes[indexMesh].vertices.size() * sizeof(fbx.meshes[indexMesh].vertices[0]);
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
				throw Coders(CODE_FAILED_BIND_VAO, "id = " + std::to_string(this->VAO));
			}
		}

		void VertexBuffer::unBind() const
		{
			glBindVertexArray(0);
		}

		void VertexBuffer::addAttribute(unsigned int location, int nElement, int offset) const
		{
		    try
		    {
		        this->bind();
		        glVertexAttribPointer(
                        location,
                        nElement,
                        Convert::convert(type),
                        GL_FALSE,
                        this->countElementToVertex * this->byteToElement,
                        (void*)(offset * static_cast<unsigned long long>(this->byteToElement)));
		        glEnableVertexAttribArray(location);
		        this->unBind();
		    }
		    catch (...)
		    {
		        throw Coders(CODE_FAILED_ADD_ATTRIBUTE_TO_VAO);
		    }
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