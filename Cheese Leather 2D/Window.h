#pragma once

#include <glfw-h>

class Window {
public:
	Window();
	~Window();

	bool shouldClose();
private:
	GLFWWindow *m_window;
	int m_width;
	int m_height;
};