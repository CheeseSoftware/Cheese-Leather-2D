#include "Game.h"
#include <iostream>

int main()
{
	Game *game = new Game();
	game->Run();
	std::cin.get();
	return 0;
}

#ifdef NOOB
/*#ifdef _WIN32
#include <Windows.h>
#elif defined linux

#endif*/

#include <iostream>

/*#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>*/
//#define GLFW_INCLUDE_GLU
#include <GLFW\glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "Octree.h"
#include "State.h"

void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(int button, int action);
void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

void Display();
void Idle();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void KeyboardKeyboard(unsigned char c, int x, int y);

State *state = nullptr;

int main(int argc, char **argv)
{
	Octree<int, 16> octree;

	//for (int i = 0; i < 64; i++)
	//	std::cout << i << ": " << octree[i] << std::endl;

	Octree<int, 16>::Element e = octree[1];  e.element = &octree;
	//octree[1] = true;

	//std::cin.get();

	for (int i = 0; i < 64; i++)
		std::cout << i << ": " << octree[i].element << std::endl;

	std::cout << octree[1337].element;


	GLFWwindow *window;

	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(800, 600, "voxicron", nullptr, nullptr);
	//glfwGetPrimaryMonitor(), nullptr);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, KeyCallback);
	/*glfwSetMouseButtonCallback(MouseButtonCallback);

	glfwSetWindowSizeCallback( reshape );
	glfwSetCharCallback( characterInput );
	glfwSetMousePosCallback( mousePos );
	glfwSetMouseWheelCallback( mouseWheel );*/


	while (!glfwWindowShouldClose(window))
	{
		int ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);//glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	/*glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Voxicron?");

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);

	glClearColor(0.125, 0.125, 0.125, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION,  lightposition);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  muljus);*/
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void ErrorCallback(int error, const char* description)
{
	fputs(description, stderr);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void MouseButtonCallback(int button, int action)
{

}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
#endif