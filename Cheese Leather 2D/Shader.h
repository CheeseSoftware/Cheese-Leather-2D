#pragma once

#include <vector>
#include <string>
#include <gl\glew.h>
#include <glm\gtc\matrix_transform.hpp>

namespace voxelengine
{



	/* An opengl shader class.
	* Don't copy this class!!!
	*/
	class Shader {
	public:
		// You cannot copy this class!
		Shader(const Shader &other) = delete;
		Shader &operator=(const Shader &other) = delete;

		Shader(const GLenum shaderType, const std::string &fileName);
		Shader(Shader &&other)
			: m_shader(other.m_shader) {
			other.m_shader = 0;
		}

		~Shader(void);

		Shader &operator=(Shader &&other) {
			m_shader = other.m_shader;
			other.m_shader = 0;
			return *this;
		}

		GLenum getShaderType();
		GLuint getShader();

	private:
		GLenum m_shaderType;

		GLuint m_shader;
	};