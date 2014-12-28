#pragma once

#include <unordered_map>
#include <string>

#include "types.h"

enum KeyState {
	KEYSTATE_UP=1,
	KEYSTATE_DOWN = 2,

	KEYSTATE_TOGGLED = 4,

	KEYSTATE_UP_TOGGLED = 5, // 4+1
	KEYSTATE_DOWN_TOGGLED = 6 // 4+2
	
};

class InputManager {
public:
		KeyState getKeyState(std::string binding);

		void bindKey(std::string binding, u32 key);

		void update();
		void pressKey(u32 key);
		void releaseKey(u32 key);
private:
	std::unordered_map<u32, KeyState> m_keys;
	std::unordered_map<std::string, u32> m_keyBindings;

	// We must update PRESSED to DOWN and RELEASED to UP.
	std::vector<u32> changedKeys;
};