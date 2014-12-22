#pragma once

class Game;
class ShaderProgram;
class Camera;

class IWorld
{
public:
	virtual ~IWorld() {}
	virtual void render(Game *game, ShaderProgram *shaderProgram, Camera *camera) = 0;
};

