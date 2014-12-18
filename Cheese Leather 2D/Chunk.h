#pragma once

#include <gl\glew.h>
#include <mutex>
#include <atomic>
#include <vector>
#include "types.h"
#include "vertex.h"

class Game;

struct BlockData
{
	// TODO: Add somethign here?
};

// TODO: Multithreading and mutexes

const int cChunkSize = 32;

class Chunk {
public:
	Chunk();
	~Chunk();


	void Render(Game *game);

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

	u16 *m_blocks;
	//std::mutex m_blockMutex;
	bool m_blocksChanged;

	BlockData *m_blockData;
	//std::mutex m_blockDataMutex;
	bool m_blockDataChanged;

	std::vector<Vertex> m_mesh;
	//std::mutex m_meshMutex;
	bool m_meshChanged;

	std::atomic<GLuint> m_vertexBuffer;
};