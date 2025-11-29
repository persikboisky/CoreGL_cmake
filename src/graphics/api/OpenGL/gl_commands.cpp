//
// Created by kisly on 19.09.2025.
//

#include "gl_commands.hpp"
#include "../../../types/color.hpp"
#include "../../../types/apiTypes.hpp"
#include "../../../package/glew-2.1.0/include/GL/glew.h"

static inline int convertPrimitive(const core::PRIMITIVE& primitive)
{
	switch (primitive)
	{
	case core::PRIMITIVE::POINTS:
		return GL_POINTS;

	case core::PRIMITIVE::TRIANGLES:
		return GL_TRIANGLES;

	case core::PRIMITIVE::LINES:
		return GL_LINES;

	case core::PRIMITIVE::LINE_STRIP:
		return GL_LINE_STRIP;

	case core::PRIMITIVE::LINE_LOOP:
		return GL_LINE_LOOP;

	case core::PRIMITIVE::TRIANGLES_FAN:
		return GL_TRIANGLE_FAN;

	case core::PRIMITIVE::TRIANGLES_STRIP:
		return GL_TRIANGLE_STRIP;

	default:
		return 0;
	}
}

namespace core
{
	namespace opengl
	{
		void drawVertex(
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

		void setPolygonMode(POLYGON fp, POLYGON_MODE mode)
		{
			int glDFP = 0;
			int glPM = 0;

			switch (fp)
			{
			case POLYGON::BACK:
				glDFP = GL_BACK;
				break;

			case POLYGON::FRONT:
				glDFP = GL_FRONT;
				break;

			default:
				glDFP = GL_FRONT_AND_BACK;
				break;
			}

			switch (mode)
			{
			case POLYGON_MODE::POINT:
				glPM = GL_POINT;
				break;

			case POLYGON_MODE::LINE:
				glPM = GL_LINE;
				break;

			case POLYGON_MODE::FILL:
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

		void setCullFace(const POLYGON& fp)
		{
			switch (fp)
			{
			case POLYGON::BACK:
				glCullFace(GL_BACK);
				break;
			case POLYGON::FRONT:
				glCullFace(GL_FRONT);
				break;
			default:
				glCullFace(GL_FRONT_AND_BACK);
				break;
			}
		}

		void setFacePolygons(const FRONT_FACE& dfp)
		{
			if (dfp == FRONT_FACE::CLOCKWISE)
				glFrontFace(GL_CW);
			else
				glFrontFace(GL_CCW);
		}

		void clearDepthBuffer()
		{
			glClear(GL_DEPTH_BUFFER_BIT);
		}

		void clearFrameBuffer()
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void setClearColor(const color::RGBA& color, bool normalize)
		{
			color::RGBA normalColor = color;
			if (normalize) normalColor.normalize();
			glClearColor(
					normalColor.red,
					normalColor.green,
					normalColor.blue,
					normalColor.alpha
			);
		}

		void setStateBlend(bool flag)
		{
			if (flag)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);
		}
	} // opengl
} // core