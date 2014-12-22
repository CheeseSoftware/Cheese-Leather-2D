#include "PlayState.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <typeindex>

#include "World.h"
#include "ShaderProgram.h"
#include "Shader.h"
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

PlayState::PlayState(Game *game) {
#ifdef CLIENT
	std::vector<Shader> defaultShaders;
	defaultShaders.emplace_back(GL_VERTEX_SHADER, "shaders\\default_Vertex.glsl");
	defaultShaders.emplace_back(GL_FRAGMENT_SHADER, "shaders\\default_Fragment.glsl");

	std::vector<std::string> defaultUniforms;
	defaultUniforms.push_back("MVP");
	defaultUniforms.push_back("baseTexture");

	m_shaderProgram = new ShaderProgram(std::move(defaultShaders));
	m_shaderProgram->addUniforms(defaultUniforms);

	m_camera = new Camera();
	m_camera->setSize(game->getWindow()->getWidth(), game->getWindow()->getHeight());
	m_position = glm::vec3(0, 0, 1.0f);
#endif

	m_world = new World();

	m_entityManager = new EntityManager();

	EntityFactory *entityFactory = game->getEntityFactory();
	{


		ComponentSprite *componentSprite = new ComponentSprite();

		ComponentPhysics *componentPhysics = new ComponentPhysics();
		componentPhysics->gravity = 1.f * glm::vec2(0.f, -1.f);
		componentPhysics->acceleration = 2.f * glm::vec2(-1.f, 0.f);
		componentPhysics->speed = 15.f * glm::vec2(0.7f,0.7f);

		ComponentUser *componentUser = new ComponentUser();

		componentSprite->texture = game->getTextureHandler()->getTexture(0);

		Entity *entityTemplate = new Entity(0);
		entityTemplate->addComponent(componentSprite);
		entityTemplate->addComponent(componentPhysics);
		entityTemplate->addComponent(componentUser);


		entityFactory->registerEntity("player", entityTemplate);
	}
	// Create player entity
	m_entityManager->addEntity(entityFactory->createEntity("player"));

	// Add systems (entity logic)
	m_entityManager->addSystem(new SystemPhysics());
	m_entityManager->addSystem(new SystemPhysicsSpriteLink());

	// Add renderSystems (entity renderers)
	m_entityManager->addRenderSystem((IRenderSystem*)(new RenderSystemSprite()));
}

PlayState::~PlayState() {
	delete m_shaderProgram;
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
	float speed = 200.0f;

	if (glfwGetKey(rawWindow, GLFW_KEY_SPACE) == GLFW_PRESS){
		m_position.z += 1 * (GLfloat)game->getDeltaTime().count() * 2;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
		m_position.z -= 1 * (GLfloat)game->getDeltaTime().count() * 2;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_D) == GLFW_PRESS){
		m_position.x += 1 * (GLfloat)game->getDeltaTime().count() * speed;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_A) == GLFW_PRESS){
		m_position.x -= 1 * (GLfloat)game->getDeltaTime().count() * speed;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_S) == GLFW_PRESS){
		m_position.y -= 1 * (GLfloat)game->getDeltaTime().count() * speed;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_W) == GLFW_PRESS){
		m_position.y += 1 * (GLfloat)game->getDeltaTime().count() * speed;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		exit(EXIT_FAILURE);
	}
	m_camera->setPosition(m_position);
	m_camera->update();

	double xpos, ypos;
	glfwGetCursorPos(rawWindow, &xpos, &ypos);
	if (glfwGetMouseButton(rawWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
		if (!rmbDown)
		{
			rmbDown = true;
			glm::vec2 pos = m_camera->toWorldPosition(glm::vec2(xpos, ypos));
			int x = pos.x / 16;
			int y = pos.y / 16;
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
			int y = pos.y / 16;
			m_world->setBlock(x, y, 1);
			std::cout << "X:" << x << " Y:" << y << std::endl;
		}
	}
	else
		lmbDown = false;
#endif

	m_entityManager->update(game, m_world);
}

void PlayState::draw(Game *game) {
#ifdef CLIENT
	m_shaderProgram->bind();
	m_world->render(game, m_shaderProgram, m_camera);
	m_entityManager->render(game, m_shaderProgram, m_camera);
	m_shaderProgram->unbind();
#endif
}