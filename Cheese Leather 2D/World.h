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

	b2World *getB2World();
private:
	b2World *m_b2World;
};

