#include "Game.h"

#include <GL\glew.h>
#include <fstream>
#include <algorithm>

#include "Window.h"
#include "PlayState.h"
#include "State.h"
#include "TextureHandler.h"


Game::Game()
{
	m_window = new Window();
	m_textureHandler = new TextureHandler();
	//m_eventhandler = new eventhandler();

#ifdef CLIENT
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "failed to initialize glew\n");
		std::cin.get();
		exit();
	}
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
#endif
	m_state = new PlayState();

	m_state->Load(this);
	m_lastFrameTime = std::chrono::system_clock::now();

	while (m_state && !m_window->getShouldClose())
	{
		std::chrono::time_point<std::chrono::system_clock> newtime = std::chrono::system_clock::now();
		m_deltaTime = newtime - m_lastFrameTime;
		//std::cout << m_deltaTime.count() << std::endl;			SPAM-sjuk sak
		m_lastFrameTime = newtime;
		m_state->Update();

#ifdef CLIENT
		m_window->Clear();
		m_state->Draw(this);
		m_window->SwapBuffers();
		glfwPollEvents();
#endif
	}
	this->exit();
}

Game::~Game() 
{
}

void Game::run() 
{

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