#include "Window.h"

#include <iostream>

Window::Window() {
#ifdef CLIENT
	if (!glfwInit())
		Error("Game", "glfwInit failed!");

	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_FSAA_SAMPLES, 4);
	//glfwWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(1200, 900, "Voxel Engine", nullptr, nullptr);

	if (!m_window)
	{
		glfwTerminate();
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	/*glfwSetErrorCallback([](int error, const char *description)
	{ Game::getGame()->Error("GLFW", description); });*/



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

bool Window::shouldClose() {
#ifdef CLIENT
	return glfwWindowShouldClose(m_window);
#else
	return false;
#endif
}

void Window::Error(const char *source, const char *description)
{
	std::cout << "ERROR " << description;
	// eventHandler->ErrorCallback(this, source, description);
}