#pragma once

class Game;

class State {
public:
	virtual ~State(void);

	virtual void Load(Game *game) { m_game = game; }

	virtual void Update()=0;
	virtual void Draw()=0;

private:
	Game *m_game;
};