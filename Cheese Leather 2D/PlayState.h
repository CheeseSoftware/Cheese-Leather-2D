#pragma once

#include "State.h"

class RandomTestRenderable;

class PlayState : public State
{
private:
	RandomTestRenderable *renderable;
public:
	PlayState();
	~PlayState();
	virtual void Load(Game *game) { m_game = game; }

	virtual void Update();
	virtual void Draw(State *state);
};

