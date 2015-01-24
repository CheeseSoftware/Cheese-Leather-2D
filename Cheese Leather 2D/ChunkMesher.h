#pragma once

#include <vector>

#include "types.h"

class Vertex;

struct BlockData;

class ChunkMesher {
public:
	void init(u16 *m_blocks);
	void run();

	void destroy();

	std::vector<Vertex> getMesh();

	bool isReady();
private:
	BlockData *m_blockData = nullptr;
	std::vector<Vertex> m_mesh;
};

struct BlockData {
	//u32 texture;
};


//#ifdef CHUNKMESHER_INCLUDED
//#pragma message ("ChunkMesher is included more than once, don't include it in header files.")
//#else
//#include CHUNKMESHER_INCLUDED
//
//class ChunkMesher {
//	template<size_t chunkSize>
//	static void generateMesh()
//};
//
//#endif
