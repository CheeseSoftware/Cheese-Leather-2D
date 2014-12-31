#pragma once

class Window;

class CEGUIManager {
public:
	CEGUIManager();
	~CEGUIManager();

	void init(Window *window);

	void update();
	void render();
private:
	Window *window;

};