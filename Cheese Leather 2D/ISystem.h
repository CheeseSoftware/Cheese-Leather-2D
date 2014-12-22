#pragma once

#include <vector>	
#include <typeinfo>
#include <typeindex>


class Entity;
class IComponent;

class ISystem {
public:
	virtual void update(Entity *entity, IComponent **components) = 0;
	virtual std::vector<std::type_index> getComponentTypes() = 0;

};
