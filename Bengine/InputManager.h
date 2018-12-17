#pragma once

#include <SDL/SDL.h>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Bengine {

class InputManager
{
public:
	InputManager();
	~InputManager();

	void update();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	void setMouseCords(float x, float y);

	/// Returns true if the key is held down
	bool isKeyDown(unsigned int keyID);

	/// Returns true if the key was just pressed
	bool isKeyPressed(unsigned int keyID);

	//GETTERS
	glm::vec2 getMouseCoords() const { return _mouseCoords; }

private:
	/// Returns true if the key is held down
	bool wasKeyDown(unsigned int keyID);


	std::unordered_map<unsigned int, bool> _keyMap;
	std::unordered_map<unsigned int, bool> _previousKeyMap;
	glm::vec2 _mouseCoords = glm::vec2(0);

};

}

