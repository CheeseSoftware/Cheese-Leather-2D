#include "SpriteBatch.h"

#include "Game.h"

#include <GL\glew.h>
#include <fstream>
#include <algorithm>

#include "Window.h"
#include "PlayState.h"
#include "State.h"
#include "TextureHandler.h"
#include "EntityFactory.h"

#include "ShaderProgram.h"
#include "Shader.h"
#include "InputManager.h"
#include "CEGUIManager.h"
#include <CEGUI\System.h>

Game::Game()
{
	m_window = new Window(800, 600);
	m_textureHandler = new TextureHandler();
	m_entityFactory = new EntityFactory();
	m_spriteBatch = new SpriteBatch();
	m_inputManager = new InputManager();
	m_ceguiManager = new CEGUIManager();


	m_window->setMouseButtonCallback([this](Window *window, int button, int action, int mods) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			if (action == GLFW_PRESS)
				this->m_ceguiManager->getInjectedInputReceiver().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
			else
				this->m_ceguiManager->getInjectedInputReceiver().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			if (action == GLFW_PRESS)
				this->m_ceguiManager->getInjectedInputReceiver().injectMouseButtonDown(CEGUI::MouseButton::RightButton);
			else
				this->m_ceguiManager->getInjectedInputReceiver().injectMouseButtonUp(CEGUI::MouseButton::RightButton);
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			if (action == GLFW_PRESS)
				this->m_ceguiManager->getInjectedInputReceiver().injectMouseButtonDown(CEGUI::MouseButton::MiddleButton);
			else
				this->m_ceguiManager->getInjectedInputReceiver().injectMouseButtonUp(CEGUI::MouseButton::MiddleButton);
			break;
		}
	});

	m_window->setCursorPosCallback([this](Window *window, double xPos, double yPos) {
		this->m_ceguiManager->getInjectedInputReceiver().injectMousePosition(xPos, yPos);
	});

	m_window->setCursorEnterCallback([this](Window *window, int entered) {
		if (entered == GL_FALSE)
			this->m_ceguiManager->getInjectedInputReceiver().injectMouseLeaves();
	});

	m_window->setScrollCallback([this](Window *window, double xOffset, double yOffset) {
		this->m_ceguiManager->getInjectedInputReceiver().injectMouseWheelChange(yOffset);
	});

	m_window->setKeyCallback([this](Window *window, int key, int scancode, int action, int mods) {

		if (this->m_inputManager) {
			if (action == GLFW_PRESS) {
				this->m_inputManager->pressKey(key);
				this->m_ceguiManager->getInjectedInputReceiver().injectKeyDown(CEGUI::Key::Scan(scancode));
			}
			else if (action == GLFW_RELEASE) {
				this->m_inputManager->releaseKey(key);
				this->m_ceguiManager->getInjectedInputReceiver().injectKeyUp(CEGUI::Key::Scan(scancode));
			}
		}
	});

	m_window->setCharCallback([this](Window *window, unsigned int codePoint) {
		if ((codePoint & 0xFF80) == 0)
			this->m_ceguiManager->getInjectedInputReceiver().injectChar(codePoint & 0x7F);
	});

	m_window->setWindowSizeCallback([this](Window *window, int width, int height) {
		glViewport(0, 0, width, height);
		CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(width, height));
	});

#ifdef CLIENT
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "failed to initialize glew\n");
		std::cin.get();
		exit();
	}
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
#endif
	
	m_spriteBatch->init();

	std::vector<Shader> defaultShaders;
	defaultShaders.emplace_back(GL_VERTEX_SHADER, "shaders\\default_Vertex.glsl");
	defaultShaders.emplace_back(GL_FRAGMENT_SHADER, "shaders\\default_Fragment.glsl");

	std::vector<std::string> defaultUniforms;
	defaultUniforms.push_back("MVP");
	defaultUniforms.push_back("baseTexture");

	m_shaderProgram = new ShaderProgram(std::move(defaultShaders));
	m_shaderProgram->addUniforms(defaultUniforms);


	m_ceguiManager->init();
}

Game::~Game() 
{
}

void Game::run() 
{
	m_state = new PlayState(this);

	m_state->load(this);
	m_lastFrameTime = std::chrono::system_clock::now();

	while (m_state && !m_window->getShouldClose())
	{

		m_window->update();
		std::chrono::time_point<std::chrono::system_clock> newtime = std::chrono::system_clock::now();
		m_deltaTime = newtime - m_lastFrameTime;
		//std::cout << m_deltaTime.count() << std::endl;			SPAM-sjuk sak
		m_lastFrameTime = newtime;
		m_inputManager->update();
		m_ceguiManager->getInjectedInputReceiver().injectTimePulse(m_deltaTime.count());
		m_state->update(this);

#ifdef CLIENT

		m_window->clear();

		m_shaderProgram->bind();
		m_spriteBatch->begin(GlyphSortType::TEXTURE);

		m_state->draw(this);

		m_spriteBatch->end();
		m_spriteBatch->renderBatch(m_shaderProgram);
		m_shaderProgram->unbind();

		m_ceguiManager->render();

		m_window->swapBuffers();
		glfwPollEvents();
#endif
	}
	this->exit();
}

void Game::exit() 
{
	glfwTerminate();
}

std::chrono::duration<double> Game::getDeltaTime() const 
{
	return m_deltaTime;
}

/******************************************
*              Private                    *
*******************************************/