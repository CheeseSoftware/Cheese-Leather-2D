#include "Window.h"

#include <iostream>

#include <gl\glew.h>
#include <GLFW\glfw3.h>

Window::Window(int width, int height) {
#ifdef CLIENT
	if (!glfwInit())
		Error("Game", "glfwInit failed!");

	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_REFRESH_RATE , 0);
	
	m_width = width;
	m_height = height;
	m_window = glfwCreateWindow(m_width, m_height, "Cheese Leather 2D", nullptr, nullptr);
	
	if (!m_window)
	{
		glfwTerminate();
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	glfwGetFramebufferSize(m_window, &m_width, &m_height);
#endif
}

Window::~Window() {
#ifdef CLIENT
	if (!m_window)
		glfwDestroyWindow(m_window);
	glfwTerminate();
#endif
}

bool Window::getShouldClose() {
#ifdef CLIENT
	return glfwWindowShouldClose(m_window);
#else
	return false;
#endif
}


void Window::Clear() {
#ifdef CLIENT
	glClear(GL_COLOR_BUFFER_BIT);
#endif
}

void Window::SwapBuffers()
{
#ifdef CLIENT
	glfwSwapBuffers(m_window);
#endif
}

void Window::Error(const char *source, const char *description)
{
#ifdef CLIENT
	std::cout << "ERROR " << description;

	// eventHandler->ErrorCallback(this, source, description);
#endif
}


int Window::getWidth() const {
	return m_width;
}
int Window::getHeight() const {
	return m_height;
}