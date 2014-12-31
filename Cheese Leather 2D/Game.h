#pragma once
#include <iostream>
#include <chrono>

class IRenderer;
class Window;
class State;
class TextureHandler;
class EntityFactory;
class SpriteBatch;
class ShaderProgram;
class InputManager;
class CEGUIManager;

namespace CEGUI { 
	class OpenGL3Renderer;
};

typedef unsigned int GLuint;

class Game {
public:
	Game();
	~Game();

	void run();
	void exit();
	
	State *getState() { return m_state;  }
	Window *getWindow() { return m_window; }
	TextureHandler *getTextureHandler() { return m_textureHandler; }
	EntityFactory *getEntityFactory() { return m_entityFactory; }
	SpriteBatch *getSpriteBatch() { return m_spriteBatch; }
	ShaderProgram *getMainShaderProgram()  { return m_shaderProgram; }
	InputManager *getInputManager() { return m_inputManager; }

	std::chrono::duration<double> getDeltaTime() const;

private:
	Window *m_window;
	State *m_state;
	TextureHandler *m_textureHandler;
	EntityFactory *m_entityFactory;
	SpriteBatch *m_spriteBatch;
	ShaderProgram *m_shaderProgram;
	InputManager *m_inputManager;
	CEGUIManager *m_ceguiManager;

	std::chrono::time_point<std::chrono::system_clock> m_lastFrameTime;
	std::chrono::duration<double> m_deltaTime;
};