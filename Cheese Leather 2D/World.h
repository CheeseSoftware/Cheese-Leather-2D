#pragma once

//#include <vector>
#include <unordered_map>



#include "IWorld.h"
#include "types.h"

class Chunk;
class ShaderProgram;
class Camera;

class b2World;

class World : IWorld
{
public:
	World();
	virtual ~World();
	virtual void update(Game *game);
	virtual void render(Game *game, ShaderProgram *shaderProgram, Camera *camera);
	u16 getBlock(i64 x, i64 y);
	void setBlock(i64 x, i64 y, u16 id);

	b2World *getB2World();
private:
	Chunk *getChunk(long x, long y);
	void generateChunk(long x, long y, u16 id = 0);

	std::unordered_map<i32vec2, Chunk*, hash<i32vec2>, hash<i32vec2>> m_chunks;

	b2World *m_b2World;
};

