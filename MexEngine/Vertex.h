#pragma once

#include <GL\glew.h>

namespace MexEngine
{
	struct Position {
		float x;
		float y;
	};

	struct Color {
		GLubyte r = 255;
		GLubyte g = 255;
		GLubyte b = 255;
		GLubyte a = 255;

		void setColor(GLubyte R, GLubyte G, GLubyte B, GLubyte A = 255) {
			r = R;
			g = G;
			b = B;
			a = A;
		}
	};

	struct UV {
		float u;
		float v;
	};

	struct Vertex {
		Position position;
		Color color;

		//UV texture coordinates.
		UV uv;

		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;

		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}

	};
}