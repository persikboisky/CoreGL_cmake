//
// Created by kisly on 19.09.2025.
//

#ifndef GL_COMMAND_HPP
#define GL_COMMAND_HPP

namespace core
{
	enum PRIMITIVE : int;
	enum FRONT_FACE : int;
	enum POLYGON_MODE : int;
	enum POLYGONS : int;

	namespace opengl
	{
		void drawVertexArray(
				const PRIMITIVE& primitive,
				int firstVert,
				int countVert);

		void drawElement(
				const PRIMITIVE& primitive,
				int countVert);

		void drawElementArray(
			const PRIMITIVE& primitive,
			int countVert,
			unsigned int* array);

		void setStateDepthTest(bool flag);
		void setStateCullFace(bool flag);

		void setPolygonMode(POLYGONS fp, POLYGON_MODE mode);
		void setCullFace(const POLYGONS& fp);
		void setFacePolygons(const FRONT_FACE& dfp);

		void clearDepthBuffer();
		void clearFrameBuffer();
	} // opengl
} // core

#endif //GL_COMMAND_HPP
