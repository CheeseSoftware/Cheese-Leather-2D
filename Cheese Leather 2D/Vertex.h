#pragma once

#include <GL\glew.h>

struct Vertex {
	GLfloat x, y;
	GLfloat depth;

	GLfloat u, v;
	GLfloat r, g, b, a;
};