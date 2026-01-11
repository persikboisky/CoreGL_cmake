//
// Created by kisly on 18.09.2025.
//

#ifndef GL_VERTEXBUFFER_HPP
#define GL_VERTEXBUFFER_HPP

#include "../../../types/apiTypes.hpp"

namespace core
{
    namespace model
    {
        class OBJ;
        class FBX;
    }

	namespace opengl
	{
		struct VertexBufferCreateInfo
		{
			const void *ptrArray = nullptr;
			int sizeOfByte = 0;
			unsigned int countElementToVertex = 0;
			TYPE valueType = TYPE::FLOAT;
		};

		class VertexBuffer
		{
		private:
			unsigned int VAO;
			unsigned int VBO;
			unsigned int countElementToVertex;
			unsigned int byteToElement;
			unsigned int sizeOfByte = 0;
			TYPE type;

            explicit VertexBuffer(const VertexBufferCreateInfo& info);

		public:
			~VertexBuffer();

			/// @brief создаёт вершинный буфер
			/// @param info объект структуры opengl::VertexBufferInfo
			/// @return объект класса opengl::VertexBuffer
			static VertexBuffer create(const VertexBufferCreateInfo& info);

			/// @brief создаёт вершинный буфер
			/// @param info объект структуры opengl::VertexBufferInfo
			/// @return указатель на объект класса opengl::VertexBuffer
			static VertexBuffer *ptrCreate(const VertexBufferCreateInfo& info);

		    static VertexBuffer create(const model::OBJ& obj, unsigned int indexMesh);
		    static VertexBuffer *ptrCreate(const model::OBJ& obj, unsigned int indexMesh);

		    static VertexBuffer create(const model::FBX& fbx, unsigned int indexMesh);
		    static VertexBuffer *ptrCreate(const model::FBX& fbx, unsigned int indexMesh);

			/// @brief прикпрепляет буфер
			void bind() const;

			/// @brief открепляет буфер
			void unBind() const;

			/// @brief добавляет или перезаписывает вершинный атрибут
			/// @param location номер атрибута (его идентификатор в location шейдера)
			/// @param nElement кол-во элементов для данного атрибута
			/// @param offset отступ(в кол-вах элементов) от начала вершины
			void addAttribute(unsigned int location, int nElement, int offset) const;

			/// @brief получает размер массива в байтах
			/// @return байты
			unsigned int getSizeOfByte() const;

			/// @brief получает кол-во вершин
			/// @return кол-во вершин
			unsigned int getCountVertex() const;
		};
	} // opengl
} // core

#endif //GL_VERTEXBUFFER_HPP
