#pragma once

#include <vector>

class ChunkMesher;

class ChunkMesherPool {
public:
	static ChunkMesherPool *getSingleton();

	ChunkMesher *acquire();
	void release(ChunkMesher *chunkMesher);

private:
	static ChunkMesher *m_singleton;

	std::vector<ChunkMesher*> m_unsuedChunkMeshers;
	std::vector<ChunkMesher*> m_usedChunkMeshers;
};