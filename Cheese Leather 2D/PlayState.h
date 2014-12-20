#pragma once

#include "State.h"

class ShaderProgram;
class RandomTestRenderable;

class PlayState : public State
{
public:
	PlayState();
	~PlayState();
	virtual void Load(Game *game) { m_game = game; }

	virtual void Update();
	virtual void Draw(State *state);

private:
	RandomTestRenderable *renderable;
	ShaderProgram *shaderProgram;
};

