#include "EntityFactory.h"
#include "Entity.h"

#include "IComponent.h"

EntityFactory::~EntityFactory() {
	for (auto pair : m_entityTemplates) {
		delete pair.second;
	}
}

/* The choosen entity will now become a template to create more entities with the same properties.
* Use createEntity(...) with its name to create clones of the entitiy.
* Make sure you aren't using the choosen entity.
* Existing entities with same names will be overwritten.
*/
void EntityFactory::registerEntity(std::string name, Entity* entityTemplate) {
	float xsize = dynamic_cast<ComponentSprite*>(entityTemplate->getComponent(std::type_index(typeid(ComponentSprite))))->scale.x;
	
	auto it = m_entityTemplates.find(name);

	if (it != m_entityTemplates.end()) {
		// Replace the entity with the new one.
		delete it->second;
		it->second = entityTemplate;
	}
	else {
		m_entityTemplates.emplace(name, entityTemplate);
	}
}

Entity *EntityFactory::createEntity(std::string name) {
	auto it = m_entityTemplates.find(name);

	if (it != m_entityTemplates.end()) {
		Entity *clone = it->second->clone();
		float xsize = dynamic_cast<ComponentSprite*>(clone->getComponent(std::type_index(typeid(ComponentSprite))))->scale.x;
		float xsize2 = dynamic_cast<ComponentSprite*>(it->second->getComponent(std::type_index(typeid(ComponentSprite))))->scale.x;
		return clone;
	}
	else
		return nullptr;
}
