#include "EntityManager.h"
#include "Entity.h"

#include "ISystem.h"
#include "IRenderSystem.h"

EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {
	// TODO: delete entities
	for (auto system : m_systems)
		delete system;

	for (auto renderSystem : m_renderSystems)
		delete renderSystem;

	for (auto pair : m_entities)
		delete pair.second;
}

void EntityManager::update() {
	for (auto system : m_systems) {
		std::vector<std::type_index> componentTypes = system->getComponentTypes();
		IComponent **componentBuffer = new IComponent*[componentTypes.size()];

		
		for (auto entityPair : m_entities) {

			bool hasMissingComponents = false;

			// Load the components to the component buffer.
			for (int i = 0; i < componentTypes.size(); ++i) {
				IComponent *component = entityPair.second->getComponent(componentTypes[i]);
				if (component != nullptr) {
					componentBuffer[i] = component;
				}
				else {
					hasMissingComponents = true;
					break;
				}
			}

			// The entity must contain all required components.
			if (hasMissingComponents)
				continue;

			// We can finally execute the system.
			system->update(entityPair.second, componentBuffer);
		}

		delete[] componentBuffer;
	}
}

void EntityManager::render() {
	for (auto system : m_renderSystems) {
		std::vector<std::type_index> componentTypes = system->getComponentTypes();
		IComponent **componentBuffer = new IComponent*[componentTypes.size()];


		for (auto entityPair : m_entities) {

			bool hasMissingComponents = false;

			// Load the components to the component buffer.
			for (int i = 0; i < componentTypes.size(); ++i) {
				IComponent *component = entityPair.second->getComponent(componentTypes[i]);
				if (component != nullptr) {
					componentBuffer[i] = component;
				}
				else {
					hasMissingComponents = true;
					break;
				}
			}

			// The entity must contain all required components.
			if (hasMissingComponents)
				continue;

			// We can finally execute the system.
			system->render(entityPair.second, componentBuffer);
		}

		delete[] componentBuffer;
	}
}


u32 EntityManager::addEntity(Entity *entity) {
	u32 id;
	// Find an unused id
	{
		if (!m_unusedEntityIds.empty()) {
			id = *(m_unusedEntityIds.end() - 1);
			m_unusedEntityIds.erase(m_unusedEntityIds.end() - 1);
		}
		else {
			id = ++m_maxEntityId;
		}
	}

	entity->id = id;
	m_entities.emplace(id, entity);

	return id;
}


void EntityManager::addSystem(ISystem *system) {

	m_systems.push_back(system);
}

void EntityManager::addRenderSystem(IRenderSystem *renderSystem) {
	m_renderSystems.push_back(renderSystem);
}


