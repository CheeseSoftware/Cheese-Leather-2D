#pragma once

#include <GLFW\glfw3.h>

class Window {
public:
	Window();
	~Window();

	bool shouldClose();
private:
	GLFWwindow *m_window;
	int m_width;
	int m_height;
};