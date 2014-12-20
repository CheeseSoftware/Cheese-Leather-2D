#pragma once

#include <GL\glew.h>

struct Vertex {
	Vertex(GLfloat x, GLfloat y, GLfloat depth, GLfloat u, GLfloat v, GLfloat r, GLfloat g, GLfloat b, GLfloat a) 
		: depth(depth)
	{
		position[0] = x;
		position[1] = y;

		uv[0] = u;
		uv[1] = v;
		
		color[0] = r;
		color[1] = g;
		color[2] = b;
		color[3] = a;
	}

	GLfloat position[2];
	GLfloat depth;

	GLfloat uv[2];
	GLfloat color[4];
};