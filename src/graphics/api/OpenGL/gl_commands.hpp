//
// Created by kisly on 19.09.2025.
//

#ifndef GL_COMMAND_HPP
#define GL_COMMAND_HPP

namespace core
{
	enum PRIMITIVE : int;
	enum POLYGON_MODE : int;
	enum DIRECT_FACE_POLYGONS : int;

	namespace opengl
	{
		void drawVertexArray(
				const PRIMITIVE& primitive,
				int firstVert,
				int countVert);

		void setStateDepthTest(bool flag);
		void setPolygonMode(DIRECT_FACE_POLYGONS fp, POLYGON_MODE mode);

		void clearDepthBuffer();
		void clearFrameBuffer();
	} // opengl
} // core

#endif //GL_COMMAND_HPP
