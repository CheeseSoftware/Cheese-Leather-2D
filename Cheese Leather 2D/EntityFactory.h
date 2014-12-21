#pragma once

#include <unordered_map>
#include <string>

class Entity;

class EntityFactory {
public:
	~EntityFactory();

	/* The choosen entity will now become a template to create more entities with the same properties.
	* Use createEntity(...) with its name to create clones of the entitiy.
	* Make sure you aren't using the choosen entity.
	*/
	void registerEntity(std::string name, Entity* entityTemplate);
	Entity *createEntity(std::string name);

private:
	std::unordered_map<std::string, Entity*> m_entityTemplates;
};