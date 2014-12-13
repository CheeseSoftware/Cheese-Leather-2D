#pragma once

#include "types.h"

class Game;

class Chunk {
public:
	Chunk();
	~Chunk();


	void Render(Game *game);

	void placeBlock(i8 x, i8 y, u16 block);
	void placeBlockWithoutLock(i8 x, i8 y, u16 block);
	void placeBlockWithoutNotify(i8 x, i8 y, u16 block);
	void placeBlockWithoutNotifyAndLock(i8 x, i8 y, u16 block);

	//boost::mutex getBlockMutex();
	u16 getBlock(i8 x, i8 y);
	u16 getBlockWithoutLock(i8 x, i8 y);

private:
	u16 *m_blocks;
	/*boost::mutex m_blockMutex;

	BlockData *m_blockData;
	boost::mutex m_blockDataMutex;

	std::vector<Vertex> m_mesh;
	boost::mutex m_meshMutex;

	boost::atomic<gluint> m_vertexBuffer;*/
};