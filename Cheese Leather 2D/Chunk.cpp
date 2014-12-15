#include "Chunk.h"

Chunk::Chunk()
	: m_blocks(nullptr)
	, m_blocksChanged(false)
	, m_blockData(nullptr)
	, m_blockDataChanged(false)
	, m_meshChanged(false)
{
}


~Chunk() {
	if (m_blocks != nullptr)
		delete[] m_blocks;
	if (m_blockData != nullptr)
		delete[] m_blockData;

	if (m_vertexBuffer)
	{
		// TODO: Destroy vertex buffer.
	}
}

void Render(Game *game) {
	// TODO: Render chunks.
}

void NotifyAll() {
	// TODO: NotifyAll (generate blockData)
}

void placeBlock(i8 x, i8 y, u16 block) {
	if (m_block == nullptr)
	{
		if (block == 0)
			return;
		else
			InitalizeBlocks();
	}

	m_blocks[y*cChunkSize + x] = block;

	m_blocksChanged = true;
}
//void placeBlockWithoutLock(i8 x, i8 y, u16 block);
//void placeBlockWithoutNotify(i8 x, i8 y, u16 block);
//void placeBlockWithoutNotifyAndLock(i8 x, i8 y, u16 block);

//std::mutex getBlockMutex();
u16 Chunk::getBlock(i8 x, i8 y) {
	if (m_blocks == nullptr)
		return nullptr;
	else
		return m_blocks[y* cChunkSize + x];
}
//u16 getBlockWithoutLock(i8 x, i8 y);
/******************************************
*              Private                    *
*******************************************/

void Chunk::initalizeBlocks() {
	m_blocks = new u16[cChunkSize*cChunkSize];
}

void Chunk::initalizeBlockData() {
	m_blockData = new u16[cChunkSize*cChunkSize];
}

void Chunk::loadMesh() {
	// TODO: loadMesh
}

void Chunk::loadVertexBuffer() {
	// TODO: loadVertexBuffer
}