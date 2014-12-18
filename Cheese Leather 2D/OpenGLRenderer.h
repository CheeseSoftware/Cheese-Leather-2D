//#ifdef CLIENT
//
//#pragma once
//
//#include <windows.h>
//
//#include "IRenderer.h"
//#include "ShaderType.h"
//
//class Shader;
//class Game;
//
//class OpenGLRenderer : public IRenderer
//{
//	GLuint VertexArrayID;
//	Shader *m_shaders[SHADER_MAX];
//	GLuint *m_uniforms;
//public:
//	OpenGLRenderer(Game *game, int width, int height);
//	~OpenGLRenderer();
//
//#pragma region Matrix rendering
//	virtual void DeleteMatrix(GLuint matrixPtr, GLuint size) override;
//	virtual void RenderMatrix(IRenderable *matrix, glm::mat4 *MVP, ShaderType shaderType) override;
//#pragma endregion
//
//	virtual void Clear(Window *window) override;
//	virtual void Render(Window *window) override;
//
//	virtual Shader *getShader(ShaderType shaderType) override;
//};
//#endif