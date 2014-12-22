#pragma once

#include <vector>	
#include <typeinfo>
#include <typeindex>


class Entity;
class IComponent;

class IRenderSystem {
public:
	virtual void render(Entity *entity, IComponent **components) = 0;
	virtual std::vector<std::type_index> getComponentTypes() = 0;

};

