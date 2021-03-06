#pragma once

#include "State.h"
#include <glm\glm.hpp>

class ShaderProgram;
class World;
class Camera;
class EntityManager;

class PlayState : public State
{
public:
	PlayState(Game *game);
	~PlayState();
	virtual void load(Game *game) { m_game = game; }

	virtual void update(Game *game);
	virtual void draw(Game *game);

private:
	Camera *m_camera;
	World *m_world;
	EntityManager *m_entityManager;

	glm::vec3 m_position = glm::vec3(0.f);
	float m_horizontalAngle = 0.0f;
	float m_verticalAngle = 0.0f;

	bool lmbDown = false;
	bool rmbDown = false;
};

