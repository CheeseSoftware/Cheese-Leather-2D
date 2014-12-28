#pragma once

#include <vector>
#include <string>
#include <GL\glew.h>

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
	inline GLuint getTextureUniform() { return m_textureUniform; };
	inline GLuint getMVPUniform() { return m_MVPUniform; };

private:
	GLuint m_program;
	std::vector<GLint> m_uniforms;

	GLuint m_textureUniform;
	GLuint m_MVPUniform;
};