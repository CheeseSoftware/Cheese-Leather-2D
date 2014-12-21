#pragma once

#include <unordered_map>

#include "types.h"

class Entity;
class ISystem;
class IRenderSystem;

class EntityManager {
public:
	EntityManager();

	void update();
	void render();

	u32 addEntity(Entity *entity);

	void addSystem(ISystem *system);
	void addRenderSystem(IRenderSystem *renderSystem);



private:
	std::unordered_map<u32, Entity> m_entities;
};