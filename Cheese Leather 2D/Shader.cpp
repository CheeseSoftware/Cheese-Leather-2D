#include <iostream>
#include <fstream>

#include "Shader.h"
#include <algorithm>
#include <vector>



static GLuint CreateShader(const std::string& source, GLenum shaderType);
static void CheckShaderError(GLuint shader, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);


Shader::Shader(const GLenum shaderType, const std::string &fileName)
	: m_shaderType(shaderType)
{
	GLint error = glGetError();
	m_shader = CreateShader(LoadShader(fileName), shaderType);
	error = glGetError();
}

Shader::~Shader(void)
{
	glDeleteShader(m_shader);
}

GLuint Shader::getShaderType()
{
	return m_shaderType;
}

GLuint Shader::getShader()
{
	return m_shader;
}


static GLuint CreateShader(const std::string& source, GLenum shaderType)
{
	GLuint shaderId = glCreateShader(shaderType);

	if (shaderId == 0)
		std::cerr << "Error: Shader creation failed!" << std::endl;

	// Compile Shader
	std::cout << "Compiling Shader: " << shaderType << std::endl;
	char const * ShaderSourcePointer = source.c_str();
	glShaderSource(shaderId, 1, &ShaderSourcePointer, NULL);
	glCompileShader(shaderId);

	CheckShaderError(shaderId, "Shader compilation failed");

	return shaderId;
}

static void CheckShaderError(GLuint shader, const std::string& errorMessage)
{
	GLint result = GL_FALSE;
	int errorLength;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);

	std::vector<char> error(errorLength);
	glGetShaderInfoLog(shader, errorLength, NULL, &error[0]);
	fprintf(stdout, "%s\n", &error[0]);
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append("\n" + line);
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}