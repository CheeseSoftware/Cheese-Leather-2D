#pragma once

class Game;

class IWorld
{
public:
	virtual ~IWorld() {}
	virtual void Render(Game *game) = 0;
};

