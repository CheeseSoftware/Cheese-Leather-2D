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

Game::Game()
{
	m_window = new Window(800, 600);
	m_textureHandler = new TextureHandler();
	m_entityFactory = new EntityFactory();
	m_spriteBatch = new SpriteBatch();
	m_inputManager = new InputManager();

	

	m_window->setKeyCallback([this](Window *window, int key, int scancode, int action, int mods){
		if (this->m_inputManager) {
			if (action == GLFW_PRESS)
				this->m_inputManager->pressKey(key);
			else if (action == GLFW_RELEASE)
				this->m_inputManager->releaseKey(key);
		}
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
		std::chrono::time_point<std::chrono::system_clock> newtime = std::chrono::system_clock::now();
		m_deltaTime = newtime - m_lastFrameTime;
		//std::cout << m_deltaTime.count() << std::endl;			SPAM-sjuk sak
		m_lastFrameTime = newtime;
		m_inputManager->update();
		m_state->update(this);

#ifdef CLIENT

		m_window->clear();

		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);*/
		m_shaderProgram->bind();
		m_spriteBatch->begin(GlyphSortType::TEXTURE);

		m_state->draw(this);

		m_spriteBatch->end();
		m_spriteBatch->renderBatch(m_shaderProgram);
		m_shaderProgram->unbind();

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