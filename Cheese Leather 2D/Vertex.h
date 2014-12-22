#pragma once

#include <GL\glew.h>

struct Vertex {
	Vertex() {
		depth = 0;
		position[0] = 0;
		position[1] = 0;

		uv[0] = 0;
		uv[1] = 0;

		color[0] = 1;
		color[1] = 0;
		color[2] = 0;
		color[3] = 1;
	}

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