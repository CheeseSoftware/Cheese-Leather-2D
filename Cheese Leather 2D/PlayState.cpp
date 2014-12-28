#include "PlayState.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <typeindex>

#include "World.h"
#include "Camera.h"
#include "Game.h"
#include "Window.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "Entity.h"
#include "IComponent.h"
#include "IRenderSystem.h"
#include "TextureHandler.h"
#include "ISystem.h"
#include "InputManager.h"

PlayState::PlayState(Game *game) {
#ifdef CLIENT


	m_camera = new Camera();
	m_camera->setSize(game->getWindow()->getWidth(), game->getWindow()->getHeight());
	m_position = glm::vec3(0, 0, 1.0f);
#endif

	m_world = new World();

	m_entityManager = new EntityManager();

	EntityFactory *entityFactory = game->getEntityFactory();
	{


		ComponentSprite *componentSprite = new ComponentSprite();

		ComponentB2Physics *componentB2Physics = new ComponentB2Physics();

		ComponentUser *componentUser = new ComponentUser();

		componentSprite->texture = game->getTextureHandler()->getTexture(0);

		Entity *entityTemplate = new Entity(0);
		entityTemplate->addComponent(componentSprite);
		entityTemplate->addComponent(componentB2Physics);
		entityTemplate->addComponent(componentUser);


		entityFactory->registerEntity("player", entityTemplate);
	}
	// Create player entity
	m_entityManager->addEntity(entityFactory->createEntity("player"), game, m_world);

	Entity *entity = entityFactory->createEntity("player");
	m_entityManager->addEntity(entity, game, m_world);
	ComponentB2Physics *physics = entity->getComponent<ComponentB2Physics>();
	physics->spawnPosition = glm::vec2(13 * 16, 37 * 16);
	physics->spawnGravity = glm::vec2(0, 0);
	physics->spawnAcceleration = glm::vec2(0, 0);
	physics->spawnVelocity = glm::vec2(0.1f, 0);

	for (int x = 8; x < 16; ++x) {
		for (int y = 8; y < 16; ++y) {
			Entity *entity = entityFactory->createEntity("player");

			ComponentB2Physics *physics = entity->getComponent<ComponentB2Physics>();
			physics->spawnPosition = glm::vec2(x * 16.f, y * 16.f);
			physics->spawnVelocity = glm::vec2(+6.4f - 0.8f*x, +6.4 - 0.8f*y + 0.5f*x);
			physics->spawnAngularVelocity = x*64.f;
			physics->spawnAngle = (float)x / 16.f*3.14;
			physics->spawnSize = fvec2(y*0.0625f, y*0.0625f);


			ComponentSprite *sprite = entity->getComponent<ComponentSprite>();
			//sprite->angle = (float)x / 16.f*3.14;
			sprite->scale = fvec2(y*0.0625f,y*0.0625f);

			m_entityManager->addEntity(entity, game, m_world);
		}
	}


	// Add systems (entity logic)
	m_entityManager->addSystem(new SystemPhysics());
	m_entityManager->addSystem(new SystemPhysicsSpriteLink());

	// Add renderSystems (entity renderers)
	m_entityManager->addRenderSystem((IRenderSystem*)(new RenderSystemSprite()));

	// Add key bindings
	{
		InputManager *inputManager = game->getInputManager();

		inputManager->bindKey(std::string("ZoomIn"), GLFW_KEY_SPACE);
		inputManager->bindKey(std::string("ZoomOut"), GLFW_KEY_LEFT_SHIFT);
	}
}

PlayState::~PlayState() {
	delete m_camera;
	delete m_world;
	delete m_entityManager;
}

void PlayState::update(Game *game) {
#ifdef CLIENT
	Window *window = game->getWindow();
	GLFWwindow *rawWindow = window->getRawWindow();
	int width = window->getWidth();
	int height = window->getHeight();
	float speed = 600.0f;
	float speedZoomModifier = pow(2.f, 1.f-m_position.z);

	InputManager *inputManager = game->getInputManager();



	//if (glfwGetKey(rawWindow, GLFW_KEY_SPACE) == GLFW_PRESS){
	if (inputManager->getKeyState("ZoomIn") == KEYSTATE_DOWN) {
		m_position.z += 1 * (GLfloat)game->getDeltaTime().count() * 4;
	}

	//if (glfwGetKey(rawWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
	if (inputManager->getKeyState("ZoomOut") == KEYSTATE_DOWN) {
		m_position.z -= 1 * (GLfloat)game->getDeltaTime().count() * 4;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_D) == GLFW_PRESS){
		m_position.x += 1 * (GLfloat)game->getDeltaTime().count() * speed * speedZoomModifier;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_A) == GLFW_PRESS){
		m_position.x -= 1 * (GLfloat)game->getDeltaTime().count() * speed * speedZoomModifier;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_S) == GLFW_PRESS){
		m_position.y -= 1 * (GLfloat)game->getDeltaTime().count() * speed * speedZoomModifier;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_W) == GLFW_PRESS){
		m_position.y += 1 * (GLfloat)game->getDeltaTime().count() * speed * speedZoomModifier;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		exit(EXIT_FAILURE);
	}

	glm::vec3 position = m_position;

	position.z = pow(2.f, position.z-1.f);

	m_camera->setPosition(position);
	m_camera->update();

	double xpos, ypos;
	glfwGetCursorPos(rawWindow, &xpos, &ypos);
	if (glfwGetMouseButton(rawWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
		if (!rmbDown)
		{
			rmbDown = true;
			glm::vec2 pos = m_camera->toWorldPosition(glm::vec2(xpos, ypos));
			int x = pos.x / 16;
			int y = pos.y / 16 + 1;
			m_world->setBlock(x, y, 0);
			std::cout << "X:" << x << " Y:" << y << std::endl;
		}
	}
	else
		rmbDown = false;
	if (glfwGetMouseButton(rawWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
		if (!lmbDown)
		{
			lmbDown = true;
			glm::vec2 pos = m_camera->toWorldPosition(glm::vec2(xpos, ypos));
			int x = pos.x / 16;
			int y = pos.y / 16 + 1;
			m_world->setBlock(x, y, 1);
			std::cout << "X:" << x << " Y:" << y << std::endl;
		}
	}
	else
		lmbDown = false;
#endif

	m_entityManager->update(game, m_world);
	m_world->update(game);
}

void PlayState::draw(Game *game) {
#ifdef CLIENT
	m_world->render(game, game->getMainShaderProgram(), m_camera);
	m_entityManager->render(game, game->getMainShaderProgram(), m_camera);
#endif
}