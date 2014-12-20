#pragma once

#include "State.h"

class World;

class PlayState : public State
{
public:
	PlayState();
	~PlayState();
	virtual void Load(Game *game) { m_game = game; }

	virtual void Update();
	virtual void Draw(Game *game);
private:
	World *world;
};

