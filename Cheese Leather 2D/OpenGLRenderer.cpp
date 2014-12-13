#ifdef CLIENT

#include "OpenglRenderer.h"

#include "Game.h"
#include "Shader.h"

OpenGLRenderer::OpenGLRenderer(Game *game, int width, int height)
{

}

OpenGLRenderer::~OpenGLRenderer()
{

}

#pragma region Matrix rendering
void OpenGLRenderer::DeleteMatrix(GLuint matrixPtr, GLuint size)
{

}

void OpenGLRenderer::RenderMatrix(IRenderable *matrix, glm::mat4 MVP, ShaderType shaderType)
{

}
#pragma endregion

void OpenGLRenderer::Clear(GLFWwindow *window)
{

}

void OpenGLRenderer::Render(GLFWwindow *window)
{

}

Shader *OpenGLRenderer::getShader(ShaderType shaderType)
{
	return m_shaders[shaderType];
}

#endif