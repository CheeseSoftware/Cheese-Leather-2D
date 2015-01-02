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
	void setMouseButtonCallback(std::function<void(Window *window, int button, int action, int mods)> mouseButtonCallback) {
		m_mouseButtonCallback = mouseButtonCallback;
	}
	void setCursorPosCallback(std::function<void(Window *window, double xPos, double yPos)> cursorPosCallback) {
		m_cursorPosCallback = cursorPosCallback;
	}
	void setCursorEnterCallback(std::function<void(Window *window, int entered)> cursorEnterCallback) {
		m_cursorEnterCallback = cursorEnterCallback;
	}
	void setScrollCallback(std::function<void(Window *window, double xOffset, double yOffset)> scrollCallback) {
		m_scrollCallback = scrollCallback;
	}
	void setKeyCallback(std::function<void(Window *window, int key, int scancode, int action, int mods)> keyCallback) {
		m_keyCallback = keyCallback;
	}
	void setCharCallback(std::function<void(Window *window, unsigned int codePoint)> charCallback) {
		m_charCallback = charCallback;
	}

private:


	GLFWwindow *m_window;
	int m_width;
	int m_height;
	void error(const char *source, const char *description);


	std::function<void(Window *window, int button, int action, int mods)> m_mouseButtonCallback;
	std::function<void(Window *window, double xPos, double yPos)> m_cursorPosCallback;
	std::function<void(Window *window, int entered)> m_cursorEnterCallback;
	std::function<void(Window *window, double xOffset, double yOffset)> m_scrollCallback;
	std::function<void(Window *window, int key, int scancode, int action, int mods)> m_keyCallback;
	std::function<void(Window *window, unsigned int codePoint)> m_charCallback;
};