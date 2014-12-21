#pragma once

#include "State.h"
#include <glm\glm.hpp>

class ShaderProgram;
class World;
class Camera;

class PlayState : public State
{
public:
	PlayState(Game *game);
	~PlayState();
	virtual void Load(Game *game) { m_game = game; }

	virtual void Update(Game *game);
	virtual void Draw(Game *game);

private:
	ShaderProgram *m_shaderProgram;
	Camera *m_camera;
	World *m_world;

	glm::vec3 m_position = glm::vec3(0.f);
	float m_horizontalAngle = 0.0f;
	float m_verticalAngle = 0.0f;
};

