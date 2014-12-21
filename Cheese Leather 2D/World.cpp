#include "World.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Chunk.h"
#include "Camera.h"


World::World()
{
	Chunk *chunk = new Chunk();


	//andragrads!
	std::function<int(int, int)> karl = [](int x, int y) -> int { return x^y ^ (x + y) % 5 ^ (x*y) % 3 <= 1; };

	std::function<int(int, int)> sven = [](int x, int y) -> int { i32 key = x | (y << 16); auto r = hash<i32>()(key); return (r%=3)==0; };

	std::function<int(int, int)> göran = [](int x, int y) -> int { return ((x / 2) ^ (y / 2)) % 2 == 0; };

	std::function<int(int, int)> bertil = [karl](int x, int y) -> int { return ((x / 2) ^ (y / 2)) % 2 == 0 || karl(x, y); };

	std::function<int(int, int)> åke = [karl](int x, int y) -> int { return x == 0 || y == 0 || x == y; };

	std::function<int(int, int)> karl_erik = [karl](int x, int y) -> int { 	
		if (((x + y) % (x | y + 1)) % 2 != 1)
		{
			return ((x + y + x / (y + 1) + y / (x + 1)) % (x | y + 1)) <= 3;
		}
		else {
			return (((x + y) % (x | y + 1)) % 4) <= 3;
		}
	};

	for (int x = 0; x < cChunkSize; ++x)
	{
		for (int y = 0; y < cChunkSize; ++y)
		{
			chunk->setBlock(x, y, 0);
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
		for (int xx = 0; xx < cChunkSize; ++xx)
		{
			for (int yy = 0; yy < cChunkSize; ++yy)
			{
				newChunk->setBlock(xx, yy, 0);
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