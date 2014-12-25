#pragma once

#include <GL\glew.h>

#include "World.h"

#include <Box2D\Box2D.h>
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Dynamics\b2World.h>
#include "Game.h"

class Texture;

class IComponent {
public:
	virtual ~IComponent() {}
	virtual IComponent *clone()=0;
	virtual void onAdd(Game *game, World *world) {}
	virtual void onRemove(Game *game, World* world) {}
};

class ComponentSprite : virtual public IComponent {
public:
	ComponentSprite() {
		vertexBuffer = 0;
	}
	virtual ~ComponentSprite() {}
	virtual IComponent *clone() {
		auto n = new ComponentSprite(*this);
		n->scale = scale;
		return n;
	}

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


class ComponentB2Physics : virtual public IComponent {
public:
	ComponentB2Physics() {

	}
	virtual ~ComponentB2Physics() {}
	virtual IComponent *clone() { return new ComponentB2Physics(*this); }

	virtual void onAdd(Game *game, World *world) {
		// Creates a "b2BodyDef", spawn state is here.
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(spawnPosition.x, spawnPosition.y);
		bodyDef.linearVelocity = b2Vec2(spawnVelocity.x, spawnVelocity.y);
		bodyDef.angularVelocity = spawnAngularVelocity;
		bodyDef.angle = spawnAngle;


		body = world->getB2World()->CreateBody(&bodyDef);

		// Creates a box-shape for collision.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(spawnSize.x * 8.0f, spawnSize.y * 8.0f);


		// Sets the shape and material properties here.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);
	}

	virtual void onRemove(Game *game, World* world) {
		body->GetWorld()->DestroyBody(body);
		body = nullptr;
	}

	b2Body* body = nullptr;

	glm::vec2 spawnAcceleration = glm::vec2(0.f, 0.f);
	glm::vec2 spawnGravity = glm::vec2(0.f, 0.f);
	glm::vec2 spawnVelocity = glm::vec2(0.f, 0.f);
	glm::vec2 spawnPosition = glm::vec2(0.f, 0.f);
	glm::vec2 spawnSize = glm::vec2(1.f, 1.f);
	float spawnAngle = 0.f;

	float spawnAngularVelocity = 0.f;

};