#pragma once

//struct GLFWwindow;
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <functional>

class Window {
public:
	Window(int width, int height);
	~Window();

	int getWidth() const;
	int getHeight() const;

	bool getShouldClose();
	GLFWwindow *getRawWindow() { return m_window; }
	void clear();
	void swapBuffers();

	/* Callback function type:
	* void keyCallback(Window *window, int key, int scancode, int action, int mods)
	*/
	void setKeyCallback(std::function<void(Window *window, int key, int scancode, int action, int mods)> keyCallback) {
		m_keyCallback = keyCallback;
	}

private:


	GLFWwindow *m_window;
	int m_width;
	int m_height;
	void error(const char *source, const char *description);

	std::function<void(Window *window, int key, int scancode, int action, int mods)> m_keyCallback;
};