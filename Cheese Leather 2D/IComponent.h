#pragma once

#include <GL\glew.h>

class Texture;

class IComponent {
public:
	virtual ~IComponent() {}
	virtual IComponent *clone()=0;
};

class ComponentSprite : virtual public IComponent {
public:
	virtual ~ComponentSprite() {}
	virtual IComponent *clone() { return new ComponentSprite(*this); }

	// Data:

	Texture *texture = nullptr;
	GLuint vertexBuffer = 0;
	glm::mat4 spriteMatrix = glm::mat4(1.f);
	glm::vec2 position = glm::vec2(0.f, 0.f);
	glm::vec2 scale = glm::vec2(1.f, 1.f);
	float angle = 0;

	bool needsMatrixUpdate = true;
};

class ComponentPhysics : virtual public IComponent {
public:
public:
	virtual ~ComponentPhysics() {}
	virtual IComponent *clone() { return new ComponentPhysics(*this); }

	// Data:

	glm::vec2 acceleration = glm::vec2(0.f, 0.f);
	glm::vec2 gravity = glm::vec2(0.f, 0.f);
	glm::vec2 speed = glm::vec2(0.f, 0.f);
	glm::vec2 position = glm::vec2(0.f, 0.f);
};

class ComponentUser : virtual public IComponent {
public:
	virtual ~ComponentUser() {}
	virtual IComponent *clone() { return new ComponentUser(*this); }

	// Data:

	glm::vec2 inputDirection = glm::vec2(0.f, 0.f);

	float speed = 256.f;
};
