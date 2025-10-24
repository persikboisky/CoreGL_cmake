//
// Created by kisly on 18.09.2025.
//

#ifndef GL_VERTEXBUFFER_HPP
#define GL_VERTEXBUFFER_HPP

#include "gl_descriptorContainer.hpp"

namespace core
{
	enum VALUE_TYPE : int;

	namespace opengl
	{
		struct VertexBufferInfo
		{
			void *ptrArray = nullptr;
			unsigned long long sizeOfByte = 0;
			unsigned int countElementToVertex = 0;
			VALUE_TYPE valueType;
		};

		class VertexBuffer : public DescriptorContainer
		{
		private:
			unsigned int VBO;
			unsigned int countElementToVertex;
			unsigned int byteToElement;
			unsigned int sizeOfByte = 0;
			VALUE_TYPE type;

			VertexBuffer(const VertexBufferInfo& info);

		public:
			~VertexBuffer();

			static VertexBuffer create(const VertexBufferInfo& info);
			static VertexBuffer *ptrCreate(const VertexBufferInfo& info);

			void bind() const override;
			void unBind() const override;

			void addAttribute(unsigned int location, int nElement, int offset) const;

			unsigned int getSizeOfByte() const;
			unsigned int getCountVertex() const;
		};
	} // opengl
} // core

#endif //GL_VERTEXBUFFER_HPP
