//
// Created by kisly on 14.07.2025.
//

#include "vao.hpp"
#include "../../util/vector.hpp"
#include "../../util/types.hpp"
#include "../../util/coders.hpp"
#include <glad/glad.h>
#include <vector>
#include <string>

using namespace core;

#pragma region vao

std::vector<unsigned int> vao::idVAO;
std::vector<unsigned int> vao::idVBO;
unsigned int vao::selectID;

unsigned int vao::getSelectId()
{
    return vao::selectID;
}

void vao::bind(unsigned int id)
{
    try
    {
        glBindVertexArray(id);
        vao::selectID = id;
    }
    catch (...)
    {
        throw coders(12, "id = " + std::to_string(id));
    }
}

unsigned int vao::create(float *data, int sizeOfByte)
{
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    if (VAO == -1)
    {
        throw coders(13);
    }

    if (VBO == -1)
    {
        throw coders(14);
    }

    vao::idVAO.push_back(VAO);
    vao::idVBO.push_back(VBO);

    bind(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfByte, data, GL_STATIC_DRAW);
    bind(0);

    return VAO;
}

[[nodiscard]] unsigned int vao::create(std::vector<float> data)
{
    return vao::create(data.data(), data.size() * sizeof(float));
}

void vao::addAttribute(unsigned int id, int index, int n, int size, int indentation)
{
    bind(id);
    try
    {
        glVertexAttribPointer(
                index,
                n,
                GL_FLOAT,
                GL_FALSE,
                size * sizeof(GLfloat),
                (GLvoid *)(indentation * sizeof(GLfloat)));
        glEnableVertexAttribArray(index);
    }
    catch (...)
    {
        throw coders(15);
    }
    bind(0);
}

void vao::Delete(unsigned int id)
{
    unsigned int index = vector::searchIndexFromValue(vao::idVAO, id);

    if (index != -1)
    {
        glDeleteVertexArrays(1, &id);
        glDeleteBuffers(1, &vao::idVBO[index]);

        std::vector<unsigned int>::const_iterator iterVAO = vao::idVAO.cbegin();
        std::vector<unsigned int>::const_iterator iterVBO = vao::idVBO.cbegin();

        vao::idVAO.erase(iterVAO + index);
        vao::idVBO.erase(iterVBO + index);
    }
}

void vao::DeleteALL()
{
    for (int i = 0; i < vao::idVAO.size(); i++)
    {
        glDeleteVertexArrays(1, &vao::idVAO[i]);
        glDeleteBuffers(1, &vao::idVBO[i]);
        // vao::id[i] = 0;
    }

    vao::idVAO.clear();
    vao::idVBO.clear();
}

void vao::draw(PRIMITIVE Primitive, int first_vert, int count_vert)
{
    glDrawArrays(convertPrimitive(Primitive), first_vert, count_vert);
}

void vao::draw(PRIMITIVE Primitive, unsigned int VAO, int first_vert, int count_vert)
{
    bind(VAO);
    glDrawArrays(convertPrimitive(Primitive), first_vert, count_vert);
    // bind(0);
}

void vao::setSizePoints(float sizePixel)
{
    glPointSize(sizePixel);
}

void vao::setWidthLine(float width)
{
    glLineWidth(width);
}

#pragma endregion

#pragma region VAO

VAO::VAO(float *data, int sizeOfByte, int elementToVert) : elementToVert(elementToVert), size(sizeOfByte / sizeof(float))
{
    this->id = vao::create(data, sizeOfByte);
}

VAO::VAO(std::vector<float> data, int elementToVert) : elementToVert(elementToVert), size(data.size())
{
    this->id = vao::create(data);
}

VAO::~VAO()
{
    vao::Delete(this->id);
}

void VAO::addAttribute(int index, int n, int indentation) const
{
    vao::addAttribute(this->id, index, n, this->elementToVert, indentation);
}

void VAO::bind() const
{
    vao::bind(this->id);
}

void VAO::draw(PRIMITIVE Primitive, int first_vert, int count_vert) const
{
    vao::setSizePoints(this->sizePoint);
    vao::setWidthLine(this->widthLine);

    if (vao::getSelectId() != this->id)
    {
        this->bind();
    }

    if (count_vert == 0)
    {
        vao::draw(Primitive, first_vert, this->size / this->elementToVert * 3);
    }
    else
    {
        vao::draw(Primitive, first_vert, count_vert);
    }
}

void VAO::setSizePoints(float sizePixel)
{
    this->sizePoint = sizePoint;
}

void VAO::setWidthLine(float width)
{
    this->widthLine = width;
}

#pragma endregion