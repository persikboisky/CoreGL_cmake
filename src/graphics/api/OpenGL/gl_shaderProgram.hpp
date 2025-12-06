//
// Created by kisly on 18.09.2025.
//

#ifndef GL_SHADERPROGRAM_HPP
#define GL_SHADERPROGRAM_HPP

typedef unsigned int uint32_t;

namespace core
{
	enum class TYPE_SHADER : int;

	namespace math
	{
		class Mat4;
		class Vec2;
		class Vec3;
		class Vec4;
	}

	namespace color
	{
		struct RGB;
		struct RGBA;
	}

	namespace opengl
	{
		/// @brief класс шейдера
		class Shader
		{
		private:
			unsigned int id;
			Shader(const TYPE_SHADER &type, const char *path);

		public:
			~Shader();

			/// @brief создаёт шейдер
			/// @param type тип шейдера (пример: VERTEX, FRAGMENT, GEOMETRY)
			/// @param path путь к файлу
			/// @return объект класса Shader
			static Shader create(const TYPE_SHADER &type, const char *path);

			/// @brief создаёт шейдер
			/// @param type тип шейдера (пример: VERTEX, FRAGMENT, GEOMETRY)
			/// @param path путь к файлу
			/// @return указатель на объект класса Shader
			static Shader *ptrCreate(const TYPE_SHADER &type, const char *path);

			/// @brief получает дескриптор шейдера
			/// @return дескриптор
			[[nodiscard]] unsigned int getId() const;
		};

		class ShaderProgram
		{
		private:
			unsigned int id;
			ShaderProgram(Shader **ptrShaders, uint32_t count);

		public:
			~ShaderProgram();

			/// @brief создаёт шейдерную программу
			/// @param ptrShaders массив указтелей на шейдеры
			/// @param count кол-во шейдеров
			/// @return объект класса ShaderProgram
			static ShaderProgram create(Shader **ptrShaders, uint32_t count);

			/// @brief создаёт шейдерную программу
			/// @param ptrShaders массив указтелей на шейдеры
			/// @param count кол-во шейдеров
			/// @return указатель на объект класса ShaderProgram
			static ShaderProgram *ptrCreate(Shader **ptrShaders, uint32_t count);

			/// @brief включает шейдерную программу
			void use() const;

			/// @brief выключает шейдерную программу
			void unUse() const;

			/// @brief передаёт значение в uniform переменную шейдеров(шейдерная программа должна бать включена)
			/// @param value значение
			/// @param name имя uniform переменной в шейдере
			void setUniform1f(float value, const char *name) const;

			/// @brief передаёт значение в uniform переменную шейдеров(шейдерная программа должна бать включена)
			/// @param vec2 значение
			/// @param name имя uniform переменной в шейдере
			void setUniform2f(const math::Vec2 &vec2, const char *name) const;

			/// @brief передаёт значение в uniform переменную шейдеров(шейдерная программа должна бать включена)
			/// @param vec3 значение
			/// @param name имя uniform переменной в шейдере
			void setUniform3f(const math::Vec3 &vec3, const char *name) const;

			// @brief передаёт значение в uniform переменную шейдеров(шейдерная программа должна бать включена)
			/// @param vec4 значение
			/// @param name имя uniform переменной в шейдере
			void setUniform4f(const math::Vec4 &vec4, const char *name) const;

			/// @brief передаёт значение в uniform переменную шейдеров(шейдерная программа должна бать включена)
			/// @param matrix значение
			/// @param name имя uniform переменной в шейдере
			void setUniformMat4(math::Mat4 matrix, const char *name) const;

			/// @brief передаёт значение в uniform переменную шейдеров(шейдерная программа должна бать включена)
			/// @param sampler значение
			/// @param name имя uniform переменной в шейдере
			void setUniformSampler2D(unsigned int sampler, const char *name) const;

			/// @brief передаёт значение в uniform переменную шейдеров(шейдерная программа должна бать включена)
			/// @param text значение
			/// @param name имя uniform переменной в шейдере
			void setUniformTextureSampler2D(class Texture &text, const char *name) const;

			/// @brief передаёт значение в uniform переменную шейдеров(шейдерная программа должна бать включена)
			/// @param color значение
			/// @param name имя uniform переменной в шейдере
			/// @param normalize надо ли преобразовть цвет в диапозон [0-1]
			void setUniformRGB(const color::RGB &color, const char *name, bool normalize = false) const;

			/// @brief передаёт значение в uniform переменную шейдеров(шейдерная программа должна бать включена)
			/// @param color значение
			/// @param name имя uniform переменной в шейдере
			/// @param normalize надо ли преобразовть цвет в диапозон [0-1]
			void setUniformRGBA(const color::RGBA &color, const char *name, bool normalize = false) const;
		};
	} // opengl
} // core

#endif // GL_SHADERPROGRAM_HPP
