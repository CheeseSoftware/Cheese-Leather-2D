#pragma once

//#include <vector>
#include <unordered_map>

#include "IWorld.h"
#include "types.h"

class Chunk;

class World : IWorld
{
public:
	World();
	~World();
	virtual void Render(Game *game);
private:
	std::unordered_map<i32vec2, Chunk*, hash<i32vec2>, hash<i32vec2>> m_chunks;

	Chunk *getChunk(long x, long y);
};

