#pragma once

#include <vector>
#include <unordered_map>

#include "types.h"
#include "TaskScheduler.h"

class Chunk;
class ThreadPool;
class Game;
class ShaderProgram;
class Camera;
class BlockRegister;

class ChunkManager {
public:
	ChunkManager(BlockRegister *blockRegister);
	~ChunkManager();

	void update(Game *game);
	void render(Game *game, ShaderProgram *shaderProgram, Camera *camera);

	BlockRegister *getBlockRegister() {
		return m_blockRegister;
	}
private:
	std::unordered_map<i32vec2, Chunk*, hash<i32vec2>, hash<i32vec2>> m_chunks;
	std::vector<i32vec2> m_unmeshedChunks;

	// Todo: Put the TaskScheduler in Game or make it to a singleton.
	TaskScheduler taskScheduler;
	BlockRegister *m_blockRegister;

};