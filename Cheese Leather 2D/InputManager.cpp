#include "InputManager.h"

KeyState InputManager::getKeyState(std::string binding) {
	auto bindigIt = m_keyBindings.find(binding);
	if (bindigIt == m_keyBindings.end())
		return KEYSTATE_UP;

	auto keyIt = m_keys.find(bindigIt->second);
	if (keyIt == m_keys.end())
		return KEYSTATE_UP;

	return keyIt->second;
}


void InputManager::bindKey(std::string binding, u32 key) {
	auto bindigIt = m_keyBindings.find(binding);

	if (bindigIt == m_keyBindings.end()) {
		m_keyBindings.emplace(binding, key);
	}
	else {
		bindigIt->second = key;
	}

	auto keyIt = m_keys.find(key);

	if (keyIt == m_keys.end()) {
		m_keys.emplace(key, KEYSTATE_UP);
	}
}


void InputManager::update() {
	for (u32 key : changedKeys) {
		auto keyIt = m_keys.find(key);
		if (keyIt != m_keys.end()) {

			if (keyIt->second == KEYSTATE_DOWN_TOGGLED)
				keyIt->second = KEYSTATE_DOWN;
			else if (keyIt->second == KEYSTATE_UP_TOGGLED)
				keyIt->second = KEYSTATE_UP;
		}
	}

	changedKeys.clear();
}

void InputManager::pressKey(u32 key) {
	auto keyIt = m_keys.find(key);
	if (keyIt != m_keys.end()) {
		keyIt->second = KEYSTATE_DOWN_TOGGLED;

		changedKeys.push_back(key);
	}
}

void InputManager::releaseKey(u32 key) {
	auto keyIt = m_keys.find(key);
	if (keyIt != m_keys.end()) {
		keyIt->second = KEYSTATE_UP_TOGGLED;

		changedKeys.push_back(key);
	}
}
