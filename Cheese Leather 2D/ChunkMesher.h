#ifdef CHUNKMESHER_INCLUDED
#pragma message ("ChunkMesher is included more than once, don't include it in header files.")
#else
#include CHUNKMESHER_INCLUDED

class ChunkMesher {
	template<size_t chunkSize>
	static void generateMesh()
};

#endif