#pragma once

#include <vector>	
#include <typeinfo>
#include <typeindex>

#include <glm\gtx\transform.hpp>

class Game;
class ShaderProgram;

class Entity;
class IComponent;

class IRenderSystem {
public:
	virtual void render(Game *game, ShaderProgram *shaderProgram, Entity *entity, IComponent **components) = 0;
	virtual std::vector<std::type_index> getComponentTypes() = 0;

};

class RenderSystemSprite {
public:
	virtual void render(Game *game, ShaderProgram *shaderProgram, Entity *entity, IComponent **components);
	virtual std::vector<std::type_index> getComponentTypes();

};
