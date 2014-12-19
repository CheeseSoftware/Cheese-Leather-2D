#pragma once

#include <GL\glew.h>

struct Vertex {
	Vertex(GLfloat x, GLfloat y, GLfloat depth, GLfloat u, GLfloat v, GLfloat r, GLfloat g, GLfloat b, GLfloat a) 
		: x(x)
		, y(y)
		, depth(depth)
		, u(u)
		, v(v)
		, r(r)
		, g(g)
		, b(b)
		, a(a)
	{

	}

	GLfloat x, y;
	GLfloat depth;

	GLfloat u, v;
	GLfloat r, g, b, a;
};