//
// Created by kisly on 18.09.2025.
//

#include "gl_shaderProgram.hpp"
#include "../../../util/types.hpp"
#include "../../../util/coders.hpp"
#include "../../../util/console.hpp"
#include "../../../file/code.hpp"
#include "../../../config.hpp"
#include "../../../math/Matrix4.hpp"
#include "../../../math/Vectors.hpp"
#include "gl_texture.hpp"
#include "../../../package/glew-2.1.0-master/include/GL/glew.h"
#include <string>
#include <iostream>

namespace core
{
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

	namespace opengl
	{
		Shader::Shader(const TYPE_SHADER& type, const char* path)
		{
			switch (type)
			{
			case VERTEX:
				this->id = glCreateShader(GL_VERTEX_SHADER);
				break;
			case GEOMETRY:
				this->id = glCreateShader(GL_GEOMETRY_SHADER);
				break;
			case FRAGMENT:
				this->id = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			}

			GLint result = GL_FALSE;
			int infoLogLength;

			std::string code = code::load(path).getStr();
			const char* ptrCode = code.c_str();

			glShaderSource(this->id, 1, &ptrCode, NULL);
			glCompileShader(this->id);

			glGetShaderiv(this->id, GL_COMPILE_STATUS, &result);
			glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);

			if (infoLogLength > 0)
			{
				char* errorMessage = new char[infoLogLength + 1];
				glGetShaderInfoLog(id, infoLogLength, NULL, errorMessage);
				std::string err = errorMessage;
				delete[] errorMessage;

				switch (type)
				{
				case core::FRAGMENT:
					throw coders(8, err);
				case core::GEOMETRY:
					throw coders(10, err);
				case core::VERTEX:
					throw coders(7, err);
				}
			}

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "Ok: compile " << nameShaderFromType(type) << " shader" << std::endl;
			}
		}

		Shader::~Shader()
		{
			glDeleteShader(this->id);
		}

		Shader Shader::create(const TYPE_SHADER& type, const char* path)
		{
			return Shader(type, path);
		}

		Shader* Shader::ptrCreate(const TYPE_SHADER& type, const char* path)
		{
			return new Shader(type, path);
		}

		unsigned int Shader::getId() const
		{
			return this->id;
		}

		ShaderProgram::ShaderProgram(Shader *shaders, uint32_t count)
		{
			this->id = glCreateProgram();
			for (uint32_t index = 0; index < count; index++)
			{
				glAttachShader(this->id, shaders[index].getId());
			}

			GLint result = GL_FALSE;
			int infoLogLength;

			glLinkProgram(this->id);

			glGetProgramiv(this->id, GL_LINK_STATUS, &result);
			glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);

			if (infoLogLength > 0)
			{
				char* errorMessage = new char[infoLogLength + 1];
				glGetProgramInfoLog(this->id, infoLogLength, NULL, errorMessage);
				std::string err = errorMessage;
				delete[] errorMessage;
				throw coders(9, err);
			}

			if (CORE_INFO)
			{
				console::printTime();
				std::cout << "OK: create shader program, id = " << this->id << std::endl;
			}
		}

		ShaderProgram::~ShaderProgram()
		{
			glDeleteProgram(this->id);
		}

		ShaderProgram ShaderProgram::create(Shader* shaders, uint32_t count)
		{
			return ShaderProgram(shaders, count);
		}

		ShaderProgram* ShaderProgram::ptrCreate(Shader* shaders, uint32_t count)
		{
			return new ShaderProgram(shaders, count);
		}

		void ShaderProgram::use()
		{
			glUseProgram(this->id);
		}

		void ShaderProgram::unUse()
		{
			glUseProgram(0);
		}

		void ShaderProgram::setUniform1f(float value, const char* name)
		{
			glUniform1f(getLocateUniform(this->id, name), value);
		}

		void ShaderProgram::setUniform2f(const math::Vector2& vec2, const char* name)
		{
			glUniform2f(getLocateUniform(this->id, name), vec2.x, vec2.y);
		}

		void ShaderProgram::setUniform3f(const math::Vector3& vec3, const char* name)
		{
			glUniform3f(getLocateUniform(this->id, name), vec3.x, vec3.y, vec3.z);
		}

		void ShaderProgram::setUniform4f(const math::Vector4& vec4, const char* name)
		{
			glUniform4f(getLocateUniform(this->id, name), vec4.x, vec4.y, vec4.z, vec4.w);
		}

		void ShaderProgram::setUniformMat4(math::Matrix4 matrix, const char* name)
		{
			glUniformMatrix4fv(
					getLocateUniform(this->id, name),
					1,
					GL_FALSE,
					matrix.getArray());
		}

		void ShaderProgram::setUniformSampler2D(Texture& text, const char* name)
		{
			glUniform1ui(getLocateUniform(this->id, name), text.getId());
		}
	} // opengl
} // core
