#include "Game.h"
#include "OpenGLRenderer.h"
#include "Window.h"
#include "PlayState.h"
#include "State.h"

#include <GL\glew.h>

Game::Game()
{
	m_window = new Window();
	//m_eventhandler = new eventhandler();

#ifdef CLIENT
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "failed to initialize glew\n");
		std::cin.get();
		exit(EXIT_FAILURE);
	}
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
#endif

	m_renderer = new OpenGLRenderer(this, 512, 512);
	m_state = new PlayState();

	m_state->Load(this);
	m_lastFrameTime = std::chrono::system_clock::now();

	while (m_state && !m_window->ShouldClose())
	{
		std::chrono::time_point<std::chrono::system_clock> newtime = std::chrono::system_clock::now();
		m_deltaTime = newtime - m_lastFrameTime;
		std::cout << m_deltaTime.count() << std::endl;
		m_lastFrameTime = newtime;
		m_state->Update();

#ifdef CLIENT
		m_renderer->Clear(m_window);
		m_state->Draw(m_state, m_renderer);
		m_window->SwapBuffers();
		glfwPollEvents();
		//m_renderer->SwapBuffers(m_window);
		//m_window->Update();
#endif
	}
	this->Exit();
}

Game::~Game() 
{
}

void Game::Run() 
{

}

void Game::Exit() 
{
	glfwTerminate();
}

std::chrono::duration<double> Game::getDeltaTime() const 
{
	return m_deltaTime;
}
