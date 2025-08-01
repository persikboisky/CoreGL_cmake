//
// Created by kisly on 14.07.2025.
//

#include "shader.hpp"
#include "Camera.hpp"
#include "../../file/code.hpp"
#include "../../config.hpp"
#include "../../util/types.hpp"
#include "../../util/vector.hpp"
#include "../../math/Matrix4.hpp"
#include "../../math/Vectors.hpp"
#include "../../Window/Window.hpp"
#include "../../util/coders.hpp"
#include "../../util/console.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace core;

#pragma region shader

std::vector<unsigned int> shader::id;
unsigned int shader::SelectID;

unsigned int shader::vID = 0;
unsigned int shader::gID = 0;
unsigned int shader::fID = 0;

std::string VertPath = "";
std::string FragPath = "";

static inline GLint getLocateUniform(GLuint shader, const char* name)
{
    GLint locate = glGetUniformLocation(shader, name);
    if (locate != -1)
    {
        return locate;
    }
    else
    {
        throw coders(11, name);
    }
}

unsigned int shader::getSelectID()
{
    return SelectID;
}

[[nodiscard]] unsigned int shader::createProgramFromCode(const char* codeVert, const char* codeFrag)
{
    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint result = GL_FALSE;
    int infoLogLength;

    glShaderSource(vertexShaderID, 1, &codeVert, NULL);
    glCompileShader(vertexShaderID);

    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, errorMessage);
        std::string err = errorMessage;
        delete[] errorMessage;
        throw coders(7, err);
    }

    if (CORE_INFO)
    {
        console::printTime();
        std::cout << "OK: compile vertex shader : ";
        std::cout << VertPath << std::endl;
    }

    glShaderSource(fragmentShaderID, 1, &codeFrag, NULL);
    glCompileShader(fragmentShaderID);

    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, errorMessage);
        std::string err = errorMessage;
        delete[] errorMessage;
        throw coders(8, err);
    }
    else
    {
        console::printTime();
        std::cout << "OK: compile fragment shader : ";
        std::cout << FragPath << std::endl;
    }

    unsigned int programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetProgramInfoLog(programID, infoLogLength, NULL, errorMessage);
        std::string err = errorMessage;
        delete[] errorMessage;
        throw coders(9, err);
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    console::printTime();
    std::cout << "OK: create shader program, id = ";
    std::cout << programID << std::endl;

    shader::id.push_back(programID);
    return programID;
}

[[nodiscard]] unsigned int shader::createProgramFromFile(const char* pathToVert, const char* pathToFrag)
{
    VertPath = pathToVert;
    FragPath = pathToFrag;

    std::string vert = code::loadStr(pathToVert);
    std::string frag = code::loadStr(pathToFrag);

    return createProgramFromCode(vert.c_str(), frag.c_str());
}

static inline std::string nameShaderFromType(TYPE_SHADER type)
{
    switch (type)
    {
        case VERTEX:
            return "Vertex";
        case GEOMETRY:
            return "Geometry";
        case FRAGMENT:
            return "Fragment";
        default:
            return "";
    }
}

void shader::compileFromCode(TYPE_SHADER type, const char* code)
{
    unsigned int id = 0;
    switch (type)
    {
        case VERTEX:
            id = glCreateShader(GL_VERTEX_SHADER);
            break;
        case GEOMETRY:
            id = glCreateShader(GL_GEOMETRY_SHADER);
            break;
        case FRAGMENT:
            id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }

    if (type == VERTEX && shader::vID != 0)
    {
        glDeleteShader(shader::vID);
    }
    else if (type == GEOMETRY && shader::gID != 0)
    {
        glDeleteShader(shader::gID);
    }
    else if (type == FRAGMENT && shader::fID != 0)
    {
        glDeleteShader(shader::fID);
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    glShaderSource(id, 1, &code, NULL);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(id, infoLogLength, NULL, errorMessage);
        std::string err = errorMessage;
        delete[] errorMessage;

        switch (type)
        {
            case core::FRAGMENT: throw coders(8, err);
            case core::GEOMETRY: throw coders(10, err);
            case core::VERTEX: throw coders(7, err);
        }
    }

    if (CORE_INFO)
    {
        console::printTime();
        std::cout << "Ok: compile " << nameShaderFromType(type) << " shader" << std::endl;
    }

    switch (type)
    {
        case VERTEX:
            shader::vID = id;
            break;
        case GEOMETRY:
            shader::gID = id;
            break;
        case FRAGMENT:
            shader::fID = id;
            break;
    }
}

void shader::compileFromFile(TYPE_SHADER type, const char* path)
{
    std::string code = code::loadStr(path);
    shader::compileFromCode(type, code.c_str());
}

[[nodiscard]] unsigned int shader::createProgram()
{
    GLint result = GL_FALSE;
    int infoLogLength;

    GLuint programID = glCreateProgram();
    if (shader::vID > 0)
        glAttachShader(programID, shader::vID);
    if (shader::gID > 0)
        glAttachShader(programID, shader::gID);
    if (shader::fID > 0)
        glAttachShader(programID, shader::fID);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetProgramInfoLog(programID, infoLogLength, NULL, errorMessage);
        std::string err = errorMessage;
        delete[] errorMessage;
        throw coders(9, err);
    }

    if (shader::vID > 0)
    {
        glDeleteShader(shader::vID);
        shader::vID = 0;
    }
    if (shader::gID > 0)
    {
        glDeleteShader(shader::gID);
        shader::gID = 0;
    }
    if (shader::fID > 0)
    {
        glDeleteShader(shader::fID);
        shader::fID = 0;
    }

    if (CORE_INFO)
    {
        console::printTime();
        std::cout << "OK: create shader program, id = " << programID << std::endl;
    }

    shader::id.push_back(programID);
    return programID;
}

void shader::use(unsigned int id)
{
    SelectID = id;
    glUseProgram(id);
}

void shader::Delete(unsigned int id)
{
    unsigned int index = vector::searchIndexFromValue(shader::id, id);

    if (index != -1)
    {
        glDeleteProgram(id);
        std::vector<unsigned int>::const_iterator iter = shader::id.cbegin();
        shader::id.erase(iter + index);
    }
}

void shader::DeleteALL()
{
    for (int i = 0; i < shader::id.size(); i++)
    {
        glDeleteProgram(shader::id[i]);
        shader::id[i] = 0;
    }
}

void shader::UniformMat4(math::Matrix4 matrix, const char* name)
{
    glUniformMatrix4fv(getLocateUniform(shader::SelectID, name), 1, GL_FALSE, matrix.getArray());
}

void shader::UniformCamMat4(Camera camera, int windowWidth, int windowHeight, const char* name)
{
    shader::UniformMat4(camera.getView() * camera.getProj(windowWidth, windowHeight), name);
}

void shader::Uniform1F(const float value, const char* name)
{
    glUniform1f(getLocateUniform(shader::SelectID, name), GLfloat(value));
}

void shader::Uniform2F(core::math::Vector2 vec2, const char* name)
{
    glUniform2f(getLocateUniform(shader::SelectID, name), vec2.x, vec2.y);
}

void shader::Uniform3F(core::math::Vector3 vec3, const char* name)
{
    glUniform3f(getLocateUniform(shader::SelectID, name), vec3.x, vec3.y, vec3.z);
}

void shader::Uniform4F(math::Vector4 vec4, const char* name)
{
    glUniform4f(getLocateUniform(shader::SelectID, name), vec4.x, vec4.y, vec4.z, vec4.w);
}

void shader::Uniform1I(int value, const char* name)
{
    glUniform1i(getLocateUniform(shader::SelectID, name), value);
}

void shader::UniformSample2D(int value, const char* name)
{
    glUniform1i(getLocateUniform(shader::SelectID, name), value);
}

void shader::UniformRGBA(const color::RGBA& color, const char* name, bool normalize)
{
    shader::Uniform4F(
            (normalize) ?
            math::Vector4(color.red, color.green, color.blue, color.alpha) / 255.0f :
            math::Vector4(color.red, color.green, color.blue, color.alpha), name
    );
}

void shader::UniformRGB(const color::RGB& color, const char* name, bool normalize)
{
    shader::Uniform3F(
            (normalize) ?
            math::Vector3(color.red, color.green, color.blue) / 255.0f :
            math::Vector3(color.red, color.green, color.blue), name
    );
}

#pragma endregion shader

#pragma region Shader

Shader::Shader(const char* pathVert, const char* pathFrag)
{
    this->id = shader::createProgramFromFile(pathVert, pathFrag);
}

Shader::Shader() : id(0)
{
}

void Shader::add(TYPE_SHADER type, const char* path)
{
    shader::compileFromFile(type, path);
}

void Shader::create()
{
    this->id = shader::createProgram();
}

Shader::~Shader()
{
    shader::Delete(this->id);
}

unsigned int Shader::getID() const
{
    return this->id;
}

void Shader::use() const
{
    shader::use(this->id);
}

void Shader::UniformMat4(math::Matrix4 matrix, const char* name) const
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::UniformMat4(matrix, name);
}

void Shader::UniformCamMat4(const Camera& camera, int windowWidth, int windowHeight, const char* name) const
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::UniformCamMat4(camera, windowWidth, windowHeight, name);
}

void core::Shader::UniformCamMat4(const Camera& camera, const Window& window, const char* name) const
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::UniformCamMat4(camera, window.getWidth(), window.getHeight(), name);
}

void Shader::Uniform1F(const float value, const char* name) const
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::Uniform1F(value, name);
}

void Shader::Uniform2F(core::math::Vector2 vec2, const char* name) const
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::Uniform2F(vec2, name);
}

void Shader::Uniform3F(core::math::Vector3 vec3, const char* name) const
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::Uniform3F(vec3, name);
}

void Shader::Uniform4F(core::math::Vector4 vec4, const char* name) const
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::Uniform4F(vec4, name);
}

void Shader::Uniform1I(int value, const char* name)
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::Uniform1I(value, name);
}

void Shader::UniformSample2D(int value, const char* name) const
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::UniformSample2D(value, name);
}

void Shader::UniformRGBA(const color::RGBA& color, const char* name, bool flag) const
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::UniformRGBA(color, name, flag);
}

void Shader::UniformRGB(const color::RGB& color, const char* name, bool flag) const
{
    if (shader::getSelectID() != this->id)
        this->use();
    shader::UniformRGB(color, name, flag);
}

#pragma endregion Shader