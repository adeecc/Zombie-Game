#include "InputManager.h"

namespace Bengine {

InputManager::InputManager() {
	//Empty	
}


InputManager::~InputManager() {
	//Empty	
}

void InputManager::update() {
	// Loop through _keyMap using for each loop and copy it over to _previousKeyMap
	for (auto& it : _keyMap) {
		_previousKeyMap[it.first] = it.second;
	}
}

void InputManager::pressKey(unsigned int keyID) {
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
	_keyMap[keyID] = false;
}

void InputManager::setMouseCords(float x, float y) {
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
	auto it = _keyMap.find(keyID);
	if(it != _keyMap.end()) {
		return it->second;
	}

	return false;
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
	//Check if it is pressed this frame, and wasnt pressed last frame
	if (isKeyDown(keyID) && !wasKeyDown(keyID)){
		return true;
	}
	return false;
}

bool InputManager::wasKeyDown(unsigned int keyID)
{
	auto it = _previousKeyMap.find(keyID);
	if (it != _previousKeyMap.end()) {
		return it->second;
	}

	return false;
}

}