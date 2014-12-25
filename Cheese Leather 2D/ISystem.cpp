#include "ISystem.h"

#include "Game.h"
#include "World.h"
#include "Entity.h"
#include "IComponent.h"

void SystemPhysics::update(Game *game, World *world, Entity *entity, IComponent **components) {
	ComponentPhysics *physics = dynamic_cast<ComponentPhysics*>(components[0]);

	physics->speed += (float)game->getDeltaTime().count() * (0.5f*physics->acceleration + 0.5f*physics->gravity);
	physics->position += (float)game->getDeltaTime().count() * physics->speed;
	physics->speed += (float)game->getDeltaTime().count() * (0.5f*physics->acceleration + 0.5f*physics->gravity);
}

std::vector<std::type_index> SystemPhysics::getComponentTypes() {
	const std::type_index type_index_array[] = {
		typeid(ComponentPhysics)
	};

	const std::vector<std::type_index> componentTypes(type_index_array, type_index_array + sizeof(type_index_array) / sizeof(type_index_array[0]));

	return componentTypes;
}

void SystemPhysicsSpriteLink::update(Game *game, World *world, Entity *entity, IComponent **components) {
	ComponentB2Physics *physics = dynamic_cast<ComponentB2Physics*>(components[0]);
	ComponentSprite *sprite = dynamic_cast<ComponentSprite*>(components[1]);

	b2Vec2 pos = physics->body->GetPosition();

	sprite->position = glm::vec2(pos.x, pos.y);
	sprite->angle = physics->body->GetAngle();
	sprite->needsMatrixUpdate = true;
}

std::vector<std::type_index> SystemPhysicsSpriteLink::getComponentTypes() {
	const std::type_index type_index_array[] = {
		typeid(ComponentB2Physics),
		typeid(ComponentSprite)
	};

	const std::vector<std::type_index> componentTypes(type_index_array, type_index_array + sizeof(type_index_array) / sizeof(type_index_array[0]));

	return componentTypes;
}