#pragma once

#include <GLFW\glfw3.h>

class Window {
public:
	Window();
	~Window();

	bool ShouldClose();
	void SwapBuffers();
private:
	GLFWwindow *m_window;
	int m_width;
	int m_height;
	virtual void Error(const char *source, const char *description);
	void Exit();
};