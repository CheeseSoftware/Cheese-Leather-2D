#pragma once

class Renderer;
class Window;
class State;

class Game {
public:
	Game();
	~Game();

	void Run();
	void Exit();

	double getDeltaTime() const;

private:
	Renderer *m_renderer;
	Window *m_window;
	State *m_state;

	double m_lastFrameTime;
	double m_deltaTime;
};