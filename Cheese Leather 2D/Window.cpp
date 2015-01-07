#include "Window.h"

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

Window::Window(int width, int height) {
#ifdef CLIENT
	if (!glfwInit())
		error("Game", "glfwInit failed!");

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

	glfwSetWindowUserPointer(m_window, this);

#pragma region input_events

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods){
		Window *_this = (Window*)glfwGetWindowUserPointer(window);
		
		if (_this->m_mouseButtonCallback)
			_this->m_mouseButtonCallback(_this, button, action, mods);
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xpos, double ypos) {
		Window *_this = (Window*)glfwGetWindowUserPointer(window);
		
		if (_this->m_cursorPosCallback)
			_this->m_cursorPosCallback(_this, xpos, ypos);
	});

	glfwSetCursorEnterCallback(m_window, [](GLFWwindow *window, int entered){
		Window *_this = (Window*)glfwGetWindowUserPointer(window);

		if (_this->m_cursorEnterCallback)
			_this->m_cursorEnterCallback(_this, entered);
	});

	glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xoffset, double yoffset){
		Window *_this = (Window*)glfwGetWindowUserPointer(window);

		if (_this->m_scrollCallback)
			_this->m_scrollCallback(_this, xoffset, yoffset);
	});

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
		Window *_this = (Window*)glfwGetWindowUserPointer(window);

		if (_this->m_keyCallback)
			_this->m_keyCallback(_this, key, scancode, action, mods);
	});


	glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int codepoint) {
		Window *_this = (Window*)glfwGetWindowUserPointer(window);

		if (_this->m_charCallback)
			_this->m_charCallback(_this, codepoint);
	});

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
		Window *_this = (Window*)glfwGetWindowUserPointer(window);

		if (_this->m_windowSizeCallback)
			_this->m_windowSizeCallback(_this, width, height);
	});
#pragma endregion
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

void Window::update() {
#ifdef CLIENT

#endif
}

void Window::clear() {
#ifdef CLIENT
	glClear(GL_COLOR_BUFFER_BIT);
#endif
}

void Window::swapBuffers() {
#ifdef CLIENT
	glfwSwapBuffers(m_window);
#endif
}

void Window::error(const char *source, const char *description) {
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