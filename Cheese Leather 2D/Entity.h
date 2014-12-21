#pragma once

#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include "types.h"

class IComponent;

struct Entity {
	Entity(u32 id)
		: id(id)
	{
	}

	~Entity();

	void addComponent(IComponent *component);
	IComponent *getComponent(std::type_index type);

	Entity *clone();

	u32 id;
	std::unordered_map<std::type_index, IComponent*> components;
};