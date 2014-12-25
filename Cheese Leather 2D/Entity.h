#pragma once

#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include "types.h"

class Game;
class IComponent;
class World;

struct Entity {
	Entity(u32 id)
		: id(id)
	{
	}

	~Entity();

	void onAdd(Game *game, World *world);
	void onRemove(Game *game, World* world);

	void addComponent(IComponent *component);
	IComponent *getComponent(std::type_index type);

	template<typename TComponent>
	TComponent *getComponent() {
		auto it = components.find(typeid(TComponent));
		if (it != components.end())
			return dynamic_cast<TComponent*>(it->second);
		else
			return nullptr;
	}

	Entity *clone();

	u32 id;
	std::unordered_map<std::type_index, IComponent*> components;
};