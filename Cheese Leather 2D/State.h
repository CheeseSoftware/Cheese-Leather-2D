#pragma once

class Game;
class IRenderer;

class State 
{
public:
	virtual void load(Game *game) { m_game = game; }

	virtual void update(Game *game) = 0;
	virtual void draw(Game *game) = 0;

protected:
	Game *m_game;
};