#pragma once

class Window;

#include <CEGUI\InjectedInputReceiver.h>

class CEGUIManager {
public:
	CEGUIManager();
	~CEGUIManager();

	void init();

	void update();
	void render();

	CEGUI::InjectedInputReceiver &getInjectedInputReceiver();
private:

};