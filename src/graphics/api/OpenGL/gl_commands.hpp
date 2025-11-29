//
// Created by kisly on 19.09.2025.
//

#ifndef GL_COMMAND_HPP
#define GL_COMMAND_HPP

namespace core
{
	enum class PRIMITIVE : int;
	enum class FRONT_FACE : int;
	enum class POLYGON_MODE : int;
	enum class POLYGON : int;

	namespace color
	{
		struct RGBA;
	}

	namespace opengl
	{
		/// @brief запускает проход рендера для вершинного буфера
		/// @param primitive примитив(пример TRIANGLES(самостоятельные треугольники))
		/// @param firstVert первая вершина
		/// @param countVert кол-во вершин
		void drawVertex(
				const PRIMITIVE& primitive,
				int firstVert,
				int countVert);

		/// @brief запускает проход рендера для индексного буфера
		/// @param primitive примитив(пример TRIANGLES(самостоятельные треугольники))
		/// @param countVert кол-во вершин
		void drawElement(
				const PRIMITIVE& primitive,
				int countVert);

		/// @brief запускает проход рендера для массива индексов
		/// @param primitive примитив(пример TRIANGLES(самостоятельные треугольники))
		/// @param countVert кол-во вершин
		/// @param array указатель на массив
		void drawElementArray(
			const PRIMITIVE& primitive,
			int countVert,
			unsigned int* array);

		/// @brief устанавливает состояние теста глубины
		/// @param flag true - включен тест глубины, false - выключен
		void setStateDepthTest(bool flag);

		/// @brief устанавливает состояние отсечения нелецивых полигонов
		/// @param flag true - включено отсечения, false - выключено
		void setStateCullFace(bool flag);

		/// @brief устанавливает тип полигонов
		/// @param fp для каких полигонов применить (пример для лицевых и задних POLYGON_FRONT_AND_BACK)
		/// @param mode тип отрисовки полигонов POLYGON_LINE (пример: отрисовка контура полигона)
		void setPolygonMode(POLYGON fp, POLYGON_MODE mode);

		/// @brief устанавливает какие полигоны отсекать
		/// @param fp вид полигона (пример: CULL_BACK - задний полигон будет осекаться)
		void setCullFace(const POLYGON& fp);

		/// @brief устанавливает какие полигоны будут лицевыми
		/// @param dfp определяет где перед (пример: FRONT_FACE_COUNTER_CLOCKWISE - 
		/// у лицевого полигона вершины идут против часовой стрелки)
		void setFacePolygons(const FRONT_FACE& dfp);

		/// @brief очищает буфер глубины
		void clearDepthBuffer();

		/// @brief очищает буфер кадра
		void clearFrameBuffer();

		/// @brief устанавливает цвет для отчистки
		/// @param color цвет
		/// @param normalize надо ли его нормализировать(то есть преобразовать в формат[0-1], 
		/// т.к. openGL использует диапозон[0-1])
		void setClearColor(const color::RGBA& color, bool normalize = false);

		void setStateBlend(bool flag);
	} // opengl
} // core

#endif //GL_COMMAND_HPP
