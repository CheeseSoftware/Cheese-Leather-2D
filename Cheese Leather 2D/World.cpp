#include "World.h"

#include "Chunk.h"

#define isColumnInsideChunkMatrix(x) x >= 0 && x < chunkMatrix.first.size()
#define isChunkInsideChunkColumn(y,x_it) y >= 0 && y < x_it.size()

World::World()
{
	Chunk *chunk = new Chunk();
	chunk->placeBlock(3, 4, 1);
	chunk->placeBlock(3, 5, 1);
	chunk->placeBlock(3, 6, 1);
	chunk->placeBlock(5, 6, 1);

	m_chunks.emplace(i32vec2(0, 0), chunk);
}


World::~World()
{
}

void World::Render(Game *game)
{
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			auto it = m_chunks.find(i32vec2(x, y));

			if (it != m_chunks.end()) {
				Chunk *chunk = it->second;

				if (chunk != nullptr) {
					chunk->Render(game);
				}
			}
		}
	}
}

/******************************************
*              Private                    *
*******************************************/

Chunk *World::getChunk(long x, long y)
{
	return nullptr;
}