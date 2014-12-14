#pragma once

//struct GLFWwindow;
#include <gl\glew.h>
#include <GLFW\glfw3.h>

class Window {
public:
	Window();
	~Window();

	bool shouldClose();

	int getWidth() const;
	int heightHeight() const;
private:
	GLFWwindow *m_window;
	int m_width;
	int m_height;
	virtual void Error(const char *source, const char *description);
	void Exit();
};