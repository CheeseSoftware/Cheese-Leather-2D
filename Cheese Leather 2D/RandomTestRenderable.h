#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "ShaderType.h"
#include "Vertex.h"

class RandomTestRenderable
{
public:
	RandomTestRenderable()
	{
		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);
		static const Vertex g_vertex_buffer_data[] = {
			Vertex(0, 0, 0, 0, 0, 1.f, 0, 0, 1.f),
			Vertex(0.5, 0, 0, 0, 0, 0, 1.f, 0, 1.f),
			Vertex(0.5, 0.5, 0, 0, 0, 0, 0, 1.f, 1.f)
		};

		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &m_vertexbuffer);

		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);

		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	}

	virtual ~RandomTestRenderable()
	{
	}

	virtual bool Render(glm::mat3 MVP)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);

		// 1rst attribute buffer : vertices
		{
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
				reinterpret_cast<void*>(offsetof(Vertex, position)));

			
		}
		//colors
		{
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
				reinterpret_cast<void*>(offsetof(Vertex, color)));

			
		}
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		return true;
	}
private:
	GLuint m_vertexbuffer;
};