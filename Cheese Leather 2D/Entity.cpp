#include "Entity.h"

#include "IComponent.h"

Entity::~Entity() {
	for (auto component : components) {
		delete component.second;
	}
}

void Entity::onAdd(Game *game, World *world) {
	for (auto componentPair : components)
		componentPair.second->onAdd(game, world);
}

void Entity::onRemove(Game *game, World* world) {
	for (auto componentPair : components)
		componentPair.second->onRemove(game, world);
}

void Entity::addComponent(IComponent *component) {
	components.emplace(typeid(*component), component);
}

IComponent *Entity::getComponent(std::type_index type) {
	auto it = components.find(type);
	if (it != components.end())
		return it->second;
	else
		return nullptr;
}

Entity *Entity::clone() {
	Entity *other = new Entity(*this);
	other->id = 0;

	for (auto &component : other->components) {
		component.second = component.second->clone();
	}

	return other;
}
