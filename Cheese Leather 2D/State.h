#pragma once

class Game;
class IRenderer;

class State 
{
public:
	virtual void Load(Game *game) { m_game = game; }

	virtual void Update()=0;
	virtual void Draw(State *state, IRenderer *renderer) = 0;

protected:
	Game *m_game;
};