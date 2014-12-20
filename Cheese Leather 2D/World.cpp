#include "World.h"

#include "Chunk.h"


World::World()
{
	Chunk *chunk = new Chunk();
	chunk->placeBlock(3, 4, 1);
	//chunk->placeBlock(3, 5, 1);
	//chunk->placeBlock(3, 6, 1);
	//chunk->placeBlock(5, 6, 1);
	m_chunks.emplace(glm::i32vec2(0, 0), chunk);
}


World::~World()
{
}

void World::Render(Game *game, ShaderProgram *shaderProgram, Camera *camera)
{
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			auto it = m_chunks.find(i32vec2(x, y));

			if (it == m_chunks.end())
				continue;

			Chunk *chunk = it->second;

			if (chunk == nullptr)
				continue;

			chunk->Render(game, shaderProgram, camera);
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