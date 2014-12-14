#pragma once
#ifdef CLIENT

#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "ShaderType.h"

class IRenderable;
class Shader;
class Window;

class IRenderer
{
protected:
	std::vector<std::pair<GLuint, GLuint>> vertexBuffers;

public:
#pragma region Matrix rendering
	virtual void DeleteMatrix(GLuint matrixPtr, GLuint size) = 0;
	virtual void RenderMatrix(IRenderable *matrix, glm::mat4 *MVP, ShaderType shaderType) = 0;
#pragma endregion

	virtual void Clear(Window *window) = 0;
	virtual void Render(Window *window) = 0;

	virtual Shader *getShader(ShaderType shaderType) = 0;
};
#endif