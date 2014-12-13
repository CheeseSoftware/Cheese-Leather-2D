#pragma once
#ifdef CLIENT

#include <vector>
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>

#include "GL.h"
#include "Color.h"
#include "ShaderType.h"


class IRenderable;
class Shader;

class IRenderer
{
protected:
	std::vector<std::pair<GLuint, GLuint>> vertexBuffers;

public:
#pragma region Matrix rendering
	virtual void DeleteMatrix(GLuint matrixPtr, GLuint size) = 0;
	virtual void RenderMatrix(IRenderable *matrix, glm::mat4 MVP, ShaderType shaderType) = 0;
#pragma endregion

	virtual void Clear(GLFWwindow *window) = 0;
	virtual void Render(GLFWwindow *window) = 0;

	virtual Shader *getShader(ShaderType shaderType) = 0;
};
#endif