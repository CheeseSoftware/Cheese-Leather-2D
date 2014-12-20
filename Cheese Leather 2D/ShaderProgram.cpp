#include <iostream>
#include <fstream>

#include "ShaderProgram.h"
#include "Shader.h"


static inline int max(int a, int b);

ShaderProgram::ShaderProgram(std::vector<Shader> &&shaders)
{
	GLint error = glGetError();

	m_program = glCreateProgram();
	error = glGetError();

	for (auto &&shader : shaders)
		glAttachShader(m_program, shader.getShader());
	error = glGetError();

	//glBindAttribLocation(m_program, 0, "position");

	// Link Program
	glLinkProgram(m_program);
	error = glGetError();

	// Check Program
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(m_program, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
	glGetProgramInfoLog(m_program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
	error = glGetError();

	// Unlink program
	//glLinkProgram(0);

}



void ShaderProgram::addUniform(std::string uniform)
{
	glLinkProgram(m_program);

	m_uniforms.push_back(glGetUniformLocation(m_program, uniform.c_str()));

	glLinkProgram(0);
}

void ShaderProgram::addUniforms(std::vector<std::string> uniforms)
{
	glLinkProgram(m_program);

	m_uniforms.reserve(uniforms.size());

	for (auto str : uniforms)
	{
		m_uniforms.push_back(glGetUniformLocation(m_program, str.c_str()));
	}

	glLinkProgram(0);
}


void ShaderProgram::bind()
{
	glUseProgram(m_program);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}

GLint ShaderProgram::getUniform(size_t index)
{
	return m_uniforms[index];
}


static inline int max(int a, int b)
{
	return (a > b) ? a : b;
}

