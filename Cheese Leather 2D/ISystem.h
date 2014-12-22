#pragma once

#include <vector>	
#include <typeinfo>
#include <typeindex>


class Entity;
class IComponent;
class World;
class Game;

class ISystem {
public:
	virtual void update(Game *game, World *world, Entity *entity, IComponent **components) = 0;
	virtual std::vector<std::type_index> getComponentTypes() = 0;
};

class SystemPhysics : virtual public ISystem {
	virtual void update(Game *game, World *world, Entity *entity, IComponent **components);
	virtual std::vector<std::type_index> getComponentTypes();
};

class SystemPhysicsSpriteLink : virtual public ISystem {
	virtual void update(Game *game, World *world, Entity *entity, IComponent **components);
	virtual std::vector<std::type_index> getComponentTypes();
};