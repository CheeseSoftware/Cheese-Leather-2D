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
	for (long x = 0; x < chunkMatrix.first.size(); ++x)
	{
		auto column = chunkMatrix.first.at(x);
		for (long y = 0; y < column.first.size(); ++y)
		{
			Chunk *chunk = column.first.at(y);
			chunk->Render(game);
		}
	}
}

/******************************************
*              Private                    *
*******************************************/

void World::Expand(long x, long y, Chunk* chunk)
{
	long xx = x + chunkMatrix.second;
	if (xx < 0)
	{
		for (long i = xx; i < 0; i++)
		{
			chunkMatrix.first.push_front(std::pair<std::deque<Chunk*>, long>(std::deque<Chunk*>(), 0));
			chunkMatrix.second++;
		}
		xx = x + chunkMatrix.second;
	}
	else if (xx >= chunkMatrix.first.size())
	{
		for (long i = 0; i <= xx; i++)
		{
			chunkMatrix.first.push_back(std::pair<std::deque<Chunk*>, long>(std::deque<Chunk*>(), 0));
		}
	}

	std::pair<std::deque<Chunk*>, long>& it = chunkMatrix.first.at(xx);
	long yy = y + it.second;

	if (yy < 0)
	{
		for (long i = yy; i < 0; i++)
		{
			it.first.push_front(nullptr);
			it.second++;
		}
		yy = y + it.second;
	}
	else if (yy >= it.first.size())
	{
		for (long i = 0; i <= yy; i++)
		{
			it.first.push_back(nullptr);
		}
	}

}

Chunk *World::getChunk(long x, long y)
{
	x += chunkMatrix.second;

	if (x >= 0)
	{
		if (isColumnInsideChunkMatrix(x))
		{
			auto it = chunkMatrix.first.at(x);
			y += it.second;

			if (y >= 0)
			{
				if (isChunkInsideChunkColumn(y, it.first))
				{
					if (it.first.at(y) != nullptr)
					{
						return it.first.at(y);
					}
				}
			}
		}
	}
	return nullptr;
}

Chunk *World::GenerateChunk(long x, long y)
{
	//TODO: Make a nice generator!
	return nullptr;


	/*Expand(x, y, nullptr);

	int xx = x + chunkMatrix.second;

	auto &it = chunkMatrix.first.at(xx);
	int yy = y + it.second;

	if (it.first.at(yy) == nullptr)
	{
	return it.first.at(yy) = generator(x, y);//(x, y, this);
	}
	return it.first.at(yy);*/

}
