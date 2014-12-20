#include "World.h"

#include "Chunk.h"

#define isColumnInsideChunkMatrix(x) x >= 0 && x < chunkMatrix.first.size()
#define isChunkInsideChunkColumn(y,x_it) y >= 0 && y < x_it.size()

World::World()
{
}


World::~World()
{
}

void World::Render(Game *game)
{

}

/******************************************
*              Private                    *
*******************************************/