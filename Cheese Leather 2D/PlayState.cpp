#include "PlayState.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "World.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Camera.h"
#include "Game.h"
#include "Window.h"

PlayState::PlayState(Game *game) {
	std::vector<Shader> defaultShaders;
	defaultShaders.emplace_back(GL_VERTEX_SHADER, "shaders\\default_Vertex.glsl");
	defaultShaders.emplace_back(GL_FRAGMENT_SHADER, "shaders\\default_Fragment.glsl");

	std::vector<std::string> defaultUniforms;
	defaultUniforms.push_back("MVP");
	defaultUniforms.push_back("baseTexture");

	m_shaderProgram = new ShaderProgram(std::move(defaultShaders));
	m_shaderProgram->addUniforms(defaultUniforms);

	m_world = new World();
	m_camera = new Camera();
	m_camera->setSize(game->getWindow()->getWidth(), game->getWindow()->getHeight());
	m_position = glm::vec3(0, 0, 1.0f);
}

PlayState::~PlayState() {
}

void PlayState::update(Game *game) {
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
		glm::vec2 pos = m_camera->toWorldPosition(glm::vec2(xpos, ypos));
		int x = pos.x / 16;
		int y = pos.y / 16;
		m_world->setBlock(x, y, 0);
		//std::cout << "X:" << x << " Y:" << y << std::endl;
	}
	if (glfwGetMouseButton(rawWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
		glm::vec2 pos = m_camera->toWorldPosition(glm::vec2(xpos, ypos));
		int x = pos.x / 16;
		int y = pos.y / 16;
		m_world->setBlock(x, y, 1);
		//std::cout << "X:" << x << " Y:" << y << std::endl;
	}
}

void PlayState::draw(Game *game) {
	m_shaderProgram->bind();
	m_world->render(game, m_shaderProgram, m_camera);
	m_shaderProgram->unbind();
}