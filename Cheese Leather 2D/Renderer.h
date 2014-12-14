#pragma once

class Window;

/* Renderer simplifies communication with opengl and communication between opengl and sfml.
* It initalizes opengl, clears current frame buffer and swap frame buffers with glfw.
*
* How to use:
* Clear();
* draw stuff...
* SwapBuffers(window);
*/
class Renderer {
public:
	Renderer();
	~Renderer();

	void Clear();
	void SwapBuffers(Window *window);
private:
};