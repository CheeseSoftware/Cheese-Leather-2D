#pragma once

//struct GLFWwindow;
#include <gl\glew.h>
#include <GLFW\glfw3.h>

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

private:
	GLFWwindow *m_window;
	int m_width;
	int m_height;
	void error(const char *source, const char *description);
};