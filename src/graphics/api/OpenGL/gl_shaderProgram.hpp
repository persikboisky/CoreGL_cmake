//
// Created by kisly on 18.09.2025.
//

#ifndef GL_SHADERPROGRAM_HPP
#define GL_SHADERPROGRAM_HPP

namespace core
{
	enum TYPE_SHADER : int;

	namespace math
	{
		class Matrix4;
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

		struct ShaderProgramInfo
		{
			Shader *ptrVertexShader = nullptr;
			Shader *ptrFragmentShader = nullptr;
			Shader *ptrGeometryShader = nullptr;
		};

		class ShaderProgram
		{
		private:
			unsigned int id = 0;

			explicit ShaderProgram(const ShaderProgramInfo& info);

		public:
			~ShaderProgram();

			static ShaderProgram create(const ShaderProgramInfo& info);
			static ShaderProgram *ptrCreate(const ShaderProgramInfo& info);

			void use();
			void unUse();

			void setUniformMat4(math::Matrix4 matrix, const char* name);
		};
	} // opengl
} // core

#endif //GL_SHADERPROGRAM_HPP
