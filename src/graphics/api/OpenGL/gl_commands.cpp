//
// Created by kisly on 19.09.2025.
//

#include "gl_commands.hpp"
#include "../../../util/types.hpp"
#include "../../../package/glew-2.1.0-master/include/GL/glew.h"

namespace core
{
	namespace opengl
	{
		void drawVertexArray(
				const PRIMITIVE& primitive,
				int firstVert,
				int countVert)
		{
			glDrawArrays(
					convertPrimitive(primitive),
					firstVert,
					countVert);
		}

		void drawElement(
				const PRIMITIVE& primitive,
				int countVert)
		{
			glDrawElements(
					convertPrimitive(primitive),
					countVert,
					GL_UNSIGNED_INT,
					(void*)0);
		}

		void drawElementArray(
				const PRIMITIVE& primitive,
				int countVert,
				unsigned int* array)
		{
			glDrawElements(
					convertPrimitive(primitive),
					countVert,
					GL_UNSIGNED_INT,
					array);
		}

		void setStateDepthTest(bool flag)
		{
			if (flag)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);
		}

		void setPolygonMode(POLYGONS fp, POLYGON_MODE mode)
		{
			int glDFP = 0;
			int glPM = 0;

			switch (fp)
			{
			case POLYGON_BACK:
				glDFP = GL_BACK;
				break;

			case POLYGON_FRONT:
				glDFP = GL_FRONT;
				break;

			default:
				glDFP = GL_FRONT_AND_BACK;
				break;
			}

			switch (mode)
			{
			case POLYGON_POINT:
				glPM = GL_POINT;
				break;

			case POLYGON_LINE:
				glPM = GL_LINE;
				break;

			default:
				glPM = GL_FILL;
				break;
			}

			glPolygonMode(glDFP, glPM);
		}

		void setStateCullFace(bool flag)
		{
			if (flag)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);
		}

		void setCullFace(const POLYGONS& fp)
		{
			switch(fp)
			{
			case POLYGON_BACK:
				glCullFace(GL_BACK);
				break;
			case POLYGON_FRONT:
				glCullFace(GL_FRONT);
				break;
			default:
				glCullFace(GL_FRONT_AND_BACK);
				break;
			}
		}

		void setFacePolygons(const FRONT_FACE & dfp)
		{
			if (dfp == FRONT_FACE_CLOCKWISE)
				glFrontFace(GL_CW);
			else
				glFrontFace(GL_CCW);
		}

		void clearDepthBuffer()
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void clearFrameBuffer()
		{
			glClear(GL_DEPTH_BUFFER_BIT);
		}


	} // opengl
} // core