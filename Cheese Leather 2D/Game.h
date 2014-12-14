#pragma once
#include <iostream>
#include <chrono>

class IRenderer;
class Window;
class State;

class Game {
public:
	Game();
	~Game();

	void Run();
	void Exit();

	std::chrono::duration<double> getDeltaTime() const;

private:
	IRenderer *m_renderer;
	Window *m_window;
	State *m_state;

	std::chrono::time_point<std::chrono::system_clock> m_lastFrameTime;
	std::chrono::duration<double> m_deltaTime;
};