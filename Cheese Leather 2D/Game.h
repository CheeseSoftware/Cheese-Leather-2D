#pragma once
#include <iostream>
#include <chrono>

class IRenderer;
class Window;
class State;
class TextureHandler;

class Game {
public:
	Game();
	~Game();

	void Run();
	void Exit();

	std::chrono::duration<double> getDeltaTime() const;

private:
	Window *m_window;
	State *m_state;
	TextureHandler *m_textureHandler;

	std::chrono::time_point<std::chrono::system_clock> m_lastFrameTime;
	std::chrono::duration<double> m_deltaTime;
};