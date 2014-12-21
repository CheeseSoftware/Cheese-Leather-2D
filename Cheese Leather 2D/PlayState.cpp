#include "PlayState.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "World.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Camera.h"
#include "Game.h"
#include "Window.h"

PlayState::PlayState(Game *game)
{
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
	m_position = glm::vec3(170,10,5);
}


PlayState::~PlayState()
{
}

void PlayState::Update(Game *game)
{
	Window *window = game->getWindow();
	GLFWwindow *rawWindow = window->getRawWindow();
	int width = window->getWidth();
	int height = window->getHeight();

	// position
	/*glm::vec3 position = glm::vec3(0, 0, 5);
	// horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	float verticalAngle = 0.0f;*/
	// Initial Field of View
	//float initialFoV = 0.0f;
	
	float speed = 50.0f; // 3 units / second
	//float mouseSpeed = 0.6f;

	//double xpos, ypos;
	//glfwGetCursorPos(rawWindow, &xpos, &ypos);
	// Reset mouse position for next frame
	//glfwSetCursorPos(rawWindow, width / 2, height / 2);
	//m_horizontalAngle += mouseSpeed * game->getDeltaTime().count() * float(width / 2 - xpos);
	//m_verticalAngle += mouseSpeed * game->getDeltaTime().count() * float(height / 2 - ypos);
	glm::vec3 direction(
		cos(m_verticalAngle) * sin(m_horizontalAngle),
		sin(m_verticalAngle),
		cos(m_verticalAngle) * cos(m_horizontalAngle)
		);
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(m_horizontalAngle - 3.14f / 2.0f),
		0,
		cos(m_horizontalAngle - 3.14f / 2.0f)
		);
	// Up vector : perpendicular to both direction and right
	glm::vec3 up = glm::cross(right, direction);
	// Move forward
	if (glfwGetKey(rawWindow, GLFW_KEY_W) == GLFW_PRESS){
		m_position.z += 1 * (GLfloat)game->getDeltaTime().count() * 2;
	}
	// Move backward
	if (glfwGetKey(rawWindow, GLFW_KEY_S) == GLFW_PRESS){
		m_position.z -= 1 * (GLfloat)game->getDeltaTime().count() * 2;
	}
	// Strafe right
	if (glfwGetKey(rawWindow, GLFW_KEY_D) == GLFW_PRESS){
		m_position += right * (GLfloat)game->getDeltaTime().count() * speed;
	}
	// Strafe left
	if (glfwGetKey(rawWindow, GLFW_KEY_A) == GLFW_PRESS){
		m_position -= right * (GLfloat)game->getDeltaTime().count() * speed;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
		m_position -= up * (GLfloat)game->getDeltaTime().count() * speed;
	}

	if (glfwGetKey(rawWindow, GLFW_KEY_SPACE) == GLFW_PRESS){
		m_position += up * (GLfloat)game->getDeltaTime().count() * speed;
	}

	//KILL THE GAME
	if (glfwGetKey(rawWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		exit(EXIT_FAILURE);
	}
	//float FoV = initialFoV - 5;
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units

	//m_camera->setAngle(m_horizontalAngle, m_verticalAngle);
	m_camera->setPosition(m_position);
	//m_camera->setFoV(FoV);
	std::cout << m_position.x << " smask " <<  m_position.y << " smask " << m_position.z << " smask " << std::endl;

	m_camera->update();
}

void PlayState::Draw(Game *game)
{
	m_shaderProgram->bind();
	//renderable->Render(glm::mat3(1.f));


	// Camera matrix
	/*// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat3 MVP;

	renderable->Render(MVP);

	
	glm::mat3 MVP;*/

	m_world->Render(game, m_shaderProgram, m_camera);
	m_shaderProgram->unbind();
}
