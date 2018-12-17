#pragma once

#include <GL/glew.h>

namespace Bengine {

class Position {
public:
	Position() : x(0), y(0) {}
	Position(float X, float Y) : x(X), y(Y) { }

	float x;
	float y;
};

class ColorRGBA8 {
public:
	ColorRGBA8() : r(0), g(0), b(0), a(0) { }
	ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
		r(R), g(G), b(B), a(A) { }

	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

class UV {
public:
	UV() : u(0), v(0) { }
	UV(float U, float V) : u(U), v(V) { }

	float u;
	float v;
};

class Vertex {
public:
	Vertex() { }
	Vertex(Position pos, ColorRGBA8 Color, UV Uv) : 
		position(pos), color(Color), uv(Uv) { }

	void setPosition(float x, float y) {
		position = Position(x, y);
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color = ColorRGBA8(r, g, b, a);
	}

	void setUV(float u, float v) {
		uv = UV(u, v);
	}

	Position position;
	ColorRGBA8 color;
	UV uv;
};

}