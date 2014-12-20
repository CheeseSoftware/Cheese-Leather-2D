#pragma once

#include <vector>
#include <string>
#include <gl\glew.h>

class Shader;

class ShaderProgram
{
public:
	ShaderProgram(std::vector<Shader> &&shaders);

	GLuint addUniform(std::string uniform);
	void addUniforms(std::vector<std::string> uniforms);

	void bind();
	void unbind();

	GLint getUniform(size_t index);

private:
	GLuint m_program;
	std::vector<GLint> m_uniforms;
};