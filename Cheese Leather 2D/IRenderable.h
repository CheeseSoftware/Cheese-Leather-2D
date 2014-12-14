#pragma once


class IRenderer;

class IRenderable
{
public:
	inline IRenderable() {}
	virtual ~IRenderable() {}
	virtual bool Render(IRenderer *renderer, glm::mat4 *MVP, ShaderType shaderType) = 0;
};