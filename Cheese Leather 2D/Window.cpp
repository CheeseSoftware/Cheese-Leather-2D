#include "Window.h"

#include <iostream>

Window::Window() 
{
#ifdef CLIENT
	if (!glfwInit())
		Error("Game", "glfwInit failed!");
	m_window = glfwCreateWindow(1200, 900, "Cheese Leather 2D", nullptr, nullptr);

	if (!m_window)
	{
		glfwTerminate();
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	//glfwGetFramebufferSize(m_window, &m_width, &m_height);
#endif
}

Window::~Window() 
{
#ifdef CLIENT
	if (!m_window)
		glfwDestroyWindow(m_window);
	glfwTerminate();
#endif
}

bool Window::ShouldClose() 
{
#ifdef CLIENT
	return glfwWindowShouldClose(m_window);
#else
	return false;
#endif
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Window::Error(const char *source, const char *description)
{
	std::cout << "ERROR " << description;
}