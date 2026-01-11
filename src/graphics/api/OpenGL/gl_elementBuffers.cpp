//
// Created by kisly on 04.10.2025.
//

#include "gl_elementBuffers.hpp"
#include "../../../util/Coders.hpp"
#include "../../../loaders/models/m_OBJ.hpp"
#include "../../../loaders/models/m_FBX.hpp"
#include <GL/glew.h>

namespace core
{
	namespace opengl
	{
		ElementBuffer::ElementBuffer(const void* array, unsigned int sizeOfByte) :
	        countVertex(sizeOfByte / sizeof(unsigned int))
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

		ElementBuffer ElementBuffer::create(const void* array, unsigned int sizeOfByte)
		{
			return ElementBuffer(array, sizeOfByte);
		}

		ElementBuffer* ElementBuffer::ptrCreate(const void* array, unsigned int sizeOfByte)
		{
			return new ElementBuffer(array, sizeOfByte);
		}

        ElementBuffer ElementBuffer::create(const model::OBJ &obj, unsigned int indexMesh)
        {
		    return ElementBuffer(
		        obj.meshes[indexMesh].indices.data(),
		        obj.meshes[indexMesh].indices.size() * sizeof(unsigned int));
        }

        ElementBuffer *ElementBuffer::ptrCreate(const model::OBJ &obj, unsigned int indexMesh)
        {
		    return new ElementBuffer(
            obj.meshes[indexMesh].indices.data(),
        obj.meshes[indexMesh].indices.size() * sizeof(unsigned int));
        }

        ElementBuffer ElementBuffer::create(const model::FBX &fbx, unsigned int indexMesh)
        {
		    return ElementBuffer(
            fbx.meshes[indexMesh].indices.data(),
        fbx.meshes[indexMesh].indices.size() * sizeof(unsigned int));
        }

        ElementBuffer *ElementBuffer::ptrCreate(const model::FBX &fbx, unsigned int indexMesh)
        {
		    return new ElementBuffer(
                fbx.meshes[indexMesh].indices.data(),
            fbx.meshes[indexMesh].indices.size() * sizeof(unsigned int));
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