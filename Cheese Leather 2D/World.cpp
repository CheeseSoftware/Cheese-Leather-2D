#include "World.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Chunk.h"
#include "Camera.h"


World::World()
{
	Chunk *chunk = new Chunk();
	for (int x = 0; x < cChunkSize; ++x)
	{
		for (int y = 0; y < cChunkSize; ++y)
		{
			chunk->setBlock(x, y, 1);
		}
	}
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

			chunk->Render(camera->getCameraMatrix() * glm::translate(glm::mat4(1.f), glm::vec3(x*cChunkSize*16, y*cChunkSize*16, 0)), game, shaderProgram, camera);
		}
	}
}

u16 World::getBlock(i64 x, i64 y)
{
	int chunkX = x/cChunkSize;
	int chunkY = y/cChunkSize;
	i8 blockX = x%cChunkSize;
	i8 blockY = y%cChunkSize;
	Chunk *chunk = m_chunks.at(i32vec2(chunkX, chunkY));
	return chunk->getBlock(blockX, blockY);
}

void World::setBlock(i64 x, i64 y, u16 id)
{
	int chunkX = x / cChunkSize;
	int chunkY = y / cChunkSize;
	i8 blockX = x%cChunkSize;
	i8 blockY = y%cChunkSize;
	auto it = m_chunks.find(i32vec2(chunkX, chunkY));
	if (it == m_chunks.end())
	{
		//return;
		Chunk *newChunk = new Chunk();
		for (int x = 0; x < cChunkSize; ++x)
		{
			for (int y = 0; y < cChunkSize; ++y)
			{
				newChunk->setBlock(x, y, 1);
			}
		}
		m_chunks.emplace(glm::i32vec2(chunkX, chunkY), newChunk);
	}

	Chunk *chunk = m_chunks.at(i32vec2(chunkX, chunkY));
	chunk->setBlock(blockX, blockY, id);
}

/******************************************
*              Private                    *
*******************************************/

Chunk *World::getChunk(long x, long y)
{
	return nullptr;
}