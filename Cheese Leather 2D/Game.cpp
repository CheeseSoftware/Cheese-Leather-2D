#include "Game.h"

#include "Renderer.h"
#include "Window.h"
#include "PlayState.h"

Game::Game() {
	m_renderer = new Renderer();
	m_window = new Window();
	m_state = new PlayState();

	m_state->load(this);





	//m_eventHandler = new EventHandler();
#ifdef CLIENT
	

	// Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//glfwSetWindowTitle( "Tutorial 01" );


	
#endif

	
	m_state->Load(this);

	m_lastFrameTime = 0; // TODO

	while (m_state && !m_window->shouldClose())
	{
		double newTime = 0; // TODO
		m_deltaTime = newTime - m_lastFrameTime;
		m_lastFrameTime = newTime;

		m_state->Update();

#ifdef CLIENT
		m_renderer->Clear(m_window);
		m_state->Draw(this, m_renderer);
		m_renderer->Render(m_window);
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
