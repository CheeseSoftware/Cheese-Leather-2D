#include "World.h"

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Chunk.h"
#include "Camera.h"
#include "Game.h"
#include "Window.h"

World::World() {
	std::function<int(int, int)> karl = [](int x, int y) -> int { return x^y ^ (x + y) % 5 ^ (x*y) % 3 <= 1; };

	std::function<int(int, int)> sven = [](int x, int y) -> int { i32 key = x | (y << 16); auto r = hash<i32>()(key); return (r %= 3) == 0; };

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

	generateChunk(0, 0, 54);
}


World::~World() {
}

void World::render(Game *game, ShaderProgram *shaderProgram, Camera *camera) {
	glm::vec2 pos = camera->toWorldPosition(glm::vec2(1, 1));
	int x = std::ceil(pos.x / 16);
	int y = std::ceil(pos.y / 16);
	int windowBlockWidth = std::ceil(game->getWindow()->getWidth() / 16);
	int windowBlockHeight = std::ceil(game->getWindow()->getHeight() / 16);
	std::vector<glm::vec2> visibleChunks;
	int startChunkX = std::ceil(x / cChunkSize) - 1;
	int startChunkY = std::ceil(y / cChunkSize) - 3;
	for (int chunkX = startChunkX; chunkX <= startChunkX + windowBlockWidth / cChunkSize + 2; chunkX++)
	{
		for (int chunkY = startChunkY; chunkY <= startChunkY + windowBlockHeight / cChunkSize + 1; chunkY++)
		{
			//std::cout << "Visible chunk: X:" << chunkX << " Y:" << chunkY << std::endl;

			auto it = m_chunks.find(i32vec2(chunkX, chunkY));

			if (it == m_chunks.end())
				continue;

			Chunk *chunk = it->second;

			if (chunk == nullptr)
				continue;

			chunk->render(camera->getCameraMatrix() * glm::translate(glm::mat4(1.f), glm::vec3(chunkX*cChunkSize * 16, chunkY*cChunkSize * 16, 0)), game, shaderProgram, camera);
		}
	}

	/*for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
		auto it = m_chunks.find(i32vec2(x, y));

		if (it == m_chunks.end())
		continue;

		Chunk *chunk = it->second;

		if (chunk == nullptr)
		continue;

		chunk->render(camera->getCameraMatrix() * glm::translate(glm::mat4(1.f), glm::vec3(x*cChunkSize*16, y*cChunkSize*16, 0)), game, shaderProgram, camera);
		}
		}*/
}

u16 World::getBlock(i64 x, i64 y) {
	int chunkX = x / cChunkSize;
	int chunkY = y / cChunkSize;
	i8 blockX = x%cChunkSize;
	i8 blockY = y%cChunkSize;
	Chunk *chunk = m_chunks.at(i32vec2(chunkX, chunkY));
	return chunk->getBlock(blockX, blockY);
}

void World::setBlock(i64 x, i64 y, u16 id) {
	int chunkX = (x < 0 ? ((double)x / cChunkSize) - 1 : ((double)x / cChunkSize));
	int chunkY = (y < 0 ? ((double)y / cChunkSize) - 1 : ((double)y / cChunkSize));
	i8 blockX = (x < 0 ? 14 - (-x - 1) % cChunkSize : x%cChunkSize);
	i8 blockY = (y < 0 ? 14 - (-y - 1) % cChunkSize : y%cChunkSize);
	auto it = m_chunks.find(i32vec2(chunkX, chunkY));
	if (it == m_chunks.end())
		generateChunk(chunkX, chunkY, 1);

	Chunk *chunk = m_chunks.at(i32vec2(chunkX, chunkY));
	chunk->setBlock(blockX, blockY, id);
}

/******************************************
*              Private                    *
*******************************************/

Chunk *World::getChunk(long x, long y) {
	auto it = m_chunks.find(i32vec2(x, y));
	if (it != m_chunks.end())
		return it->second;
	return nullptr;
}

void World::generateChunk(long x, long y, u16 id) {
	auto oldChunk = m_chunks.find(i32vec2(x, y));
	if (oldChunk != m_chunks.end())
		delete oldChunk->second;

	Chunk *newChunk = new Chunk();
	for (int xx = 0; xx < cChunkSize; ++xx)
	{
		for (int yy = 0; yy < cChunkSize; ++yy)
		{
			newChunk->setBlock(xx, yy, id);
		}
	}
	m_chunks.emplace(glm::i32vec2(x, y), newChunk);
}