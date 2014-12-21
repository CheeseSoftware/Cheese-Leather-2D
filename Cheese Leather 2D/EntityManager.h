#pragma once

#include <unordered_map>

#include "types.h"

class Entity;
class ISystem;
class IRenderSystem;

class EntityManager {
public:
	EntityManager();
	~EntityManager();

	void update();
	void render();

	u32 addEntity(Entity *entity);

	void addSystem(ISystem *system);
	void addRenderSystem(IRenderSystem *renderSystem);



private:
	std::unordered_map<u32, Entity> m_entities;

	std::vector<ISystem*> m_systems;
	std::vector<IRenderSystem*> m_renderSystems;

	u32 m_maxEntityId;
	std::vector<u32> m_unusedEntityIds;
};