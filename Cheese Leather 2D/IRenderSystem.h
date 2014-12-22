#pragma once

#include <vector>	
#include <typeinfo>
#include <typeindex>

#include <glm\gtx\transform.hpp>

class Game;
class ShaderProgram;

class Entity;
class IComponent;
class Camera;

class IRenderSystem {
public:
	virtual void render(Game *game, ShaderProgram *shaderProgram, Camera *camera, Entity *entity, IComponent **components) = 0;
	virtual std::vector<std::type_index> getComponentTypes() = 0;

};

class RenderSystemSprite : virtual public IRenderSystem {
public:
	virtual void render(Game *game, ShaderProgram *shaderProgram, Camera *camera, Entity *entity, IComponent **components);
	virtual std::vector<std::type_index> getComponentTypes();

};
