#pragma once

#include <gl\glew.h>
#include <mutex>
#include <atomic>
#include <vector>
#include "types.h"
#include "Vertex.h"

class Game;
class ShaderProgram;
class Camera;

struct BlockData
{
	// TODO: Add somethign here?
};

// TODO: Multithreading and mutexes

const int cChunkSize = 32;

class Chunk {
public:
	Chunk();
	~Chunk(void);


	void Render(Game *game, ShaderProgram *shaderProgram, Camera *camera);

	void NotifyAll();

	void placeBlock(i8 x, i8 y, u16 block);
	//void placeBlockWithoutLock(i8 x, i8 y, u16 block);
	//void placeBlockWithoutNotify(i8 x, i8 y, u16 block);
	//void placeBlockWithoutNotifyAndLock(i8 x, i8 y, u16 block);

	//std::mutex getBlockMutex();
	u16 getBlock(i8 x, i8 y);
	//u16 getBlockWithoutLock(i8 x, i8 y);

private:
	void initalizeBlocks();
	void initalizeBlockData();

	void loadMesh();
	void loadVertexBuffer();

	u16 *m_blocks = nullptr;
	//std::mutex m_blockMutex;
	bool m_isBlocksChanged = false;

	BlockData *m_blockData = nullptr;
	//std::mutex m_blockDataMutex;
	bool m_isBlockDataChanged = false;

	std::vector<Vertex> m_mesh;
	//std::mutex m_meshMutex;
	bool m_isMeshChanged = false;

	GLuint m_vertexBuffer = 0;
	GLuint m_vertexBufferSize = 0;
};