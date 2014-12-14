#pragma once

#include "State.h"

class IRenderable;

class PlayState : public State
{
private:
	IRenderable *renderable;
public:
	PlayState();
	~PlayState();
	virtual void Load(Game *game) { m_game = game; }

	virtual void Update();
	virtual void Draw(State *state, IRenderer *renderer);
};

