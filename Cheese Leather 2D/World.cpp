#include "World.h"

#include "Chunk.h"


World::World()
{
}


World::~World()
{
}

void World::Render(Game *game)
{
<<<<<<< HEAD
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			auto it = m_chunks.find(i32vec2(x, y));

			if (it == m_chunks.end())
				continue;

			Chunk *chunk = it->second;

			if (chunk == nullptr)
				continue;

			chunk->Render(game);
		}
	}
=======

>>>>>>> 43788811d3ad1f01578a98bc99667ac19445ded8
}

/******************************************
*              Private                    *
<<<<<<< HEAD
*******************************************/

Chunk *World::getChunk(long x, long y)
{
	return nullptr;
}
=======
*******************************************/
>>>>>>> 43788811d3ad1f01578a98bc99667ac19445ded8
