#pragma once

//#include <vector>
#include <deque>

#include "IWorld.h"

class Chunk;

class World : IWorld
{
public:
	World();
	~World();
	virtual void Render(Game *game);
private:
	std::pair<std::deque<std::pair<std::deque<Chunk*>, long>>, long> chunkMatrix;

	void Expand(long x, long y, Chunk* chunk);
	Chunk *getChunk(long x, long y);
	Chunk *GenerateChunk(long x, long y);
};

