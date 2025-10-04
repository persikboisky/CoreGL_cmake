//
// Created by kisly on 18.09.2025.
//

#ifndef GL_SHADERPROGRAM_HPP
#define GL_SHADERPROGRAM_HPP

typedef unsigned int uint32_t;

namespace core
{
	enum TYPE_SHADER : int;

	namespace math
	{
		class Matrix4;
		class Vector2;
		class Vector3;
		class Vector4;
	}

	namespace opengl
	{
		class Shader
		{
		private:
			unsigned int id = 0;

			Shader(const TYPE_SHADER& type, const char* path);

		public:
			~Shader();

			static Shader create(const TYPE_SHADER& type, const char* path);
			static Shader *ptrCreate(const TYPE_SHADER& type, const char* path);

			[[nodiscard]] unsigned int getId() const;
		};

		class ShaderProgram
		{
		private:
			unsigned int id = 0;

			ShaderProgram(Shader *shaders, uint32_t count);

		public:
			~ShaderProgram();

			static ShaderProgram create(Shader* shaders, uint32_t count);
			static ShaderProgram *ptrCreate(Shader* shaders, uint32_t count);

			void use();
			void unUse();

			void setUniform1f(float value, const char* name);
			void setUniform2f(const math::Vector2& vec2, const char* name);
			void setUniform3f(const math::Vector3& vec3, const char* name);
			void setUniform4f(const math::Vector4& vec4, const char* name);
			void setUniformMat4(math::Matrix4 matrix, const char* name);
			void setUniformSampler2D(class Texture& text, const char* name);
		};
	} // opengl
} // core

#endif //GL_SHADERPROGRAM_HPP
