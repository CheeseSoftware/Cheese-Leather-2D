#include "Game.h"
#include "Renderer.h"
#include "Window.h"
#include "PlayState.h"
#include "State.h"

Game::Game() {
	m_renderer = new Renderer();
	m_window = new Window();
	m_state = new PlayState();
	m_state->Load(this);
	//m_eventhandler = new eventhandler();

#ifdef CLIENT
	// initialize glew
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "failed to initialize glew\n");
		std::cin.get();
		exit(EXIT_FAILURE);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glfwsetwindowtitle( "tutorial 01" );
#endif
	
	m_state->Load(this);
	m_lastFrameTime = 0; // todo

	while (m_state && !m_window->shouldClose())
	{
		double newtime = 0; // todo
		m_deltaTime = newtime - m_lastFrameTime;
		m_lastFrameTime = newtime;
		m_state->Update();

#ifdef CLIENT
		m_renderer->Clear();
		m_state->Draw(this, m_renderer);
		m_renderer->SwapBuffers(m_window);
		m_window->Update();
#endif
	}
	this->Exit();
}

Game::~Game() {
}

void Game::Run() {

}

void Game::Exit() {

}

double Game::getDeltaTime() const {

}
