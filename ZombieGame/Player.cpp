#include "Player.h"
#include <SDL/SDL.h>
#include "Gun.h"

Player::Player() {
	//Empty	
}


Player::~Player() {
	//Empty	
}

void Player::init(float speed, 
	glm::vec2 pos,
	Bengine::InputManager* inputManager, 
	Bengine::Camera2D* camera,
	std::vector<Bullet>* bullets) {

	_speed = speed;
	_position = pos;
	_color = Bengine::ColorRGBA8(72, 172, 240, 255);
	_health = 150;

	_inputManager = inputManager;
	_camera = camera;
	_bullets = bullets;

}

void Player::addGun(Gun * gun) {
	// Add gun to inventory
	_guns.push_back(gun);

	// If no gun equipped, equip gun
	if (_currentGunIndex == -1) {
		_currentGunIndex = 0;
	}
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	float deltaTime)
{
	if (_inputManager->isKeyDown(SDLK_w)) {
		_position.y += _speed * deltaTime;
	} else if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= _speed * deltaTime;
	}

	if (_inputManager->isKeyDown(SDLK_a)) {
		_position.x -= _speed * deltaTime;
	} else if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += _speed * deltaTime;
	}

	if (_inputManager->isKeyDown(SDLK_1) && _guns.size() >= 0) {
		_currentGunIndex = 0;
	}
	else if (_inputManager->isKeyDown(SDLK_2) && _guns.size() >= 1) {
		_currentGunIndex = 1;
	}
	else if (_inputManager->isKeyDown(SDLK_3) && _guns.size() >= 2) {
		_currentGunIndex = 2;
	}
	
	if (_currentGunIndex != -1) {
		glm::vec2 mouseCoords = _inputManager->getMouseCoords();
		mouseCoords = _camera->convertScreenToWorld(mouseCoords);

		glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
		glm::vec2 direction = glm::normalize(mouseCoords - centerPosition);

		_guns[_currentGunIndex]->update(_inputManager->isKeyDown(SDL_BUTTON_LEFT), 
										centerPosition,
										direction, 
										*_bullets,
										deltaTime);
	}
	collideWithLevel(levelData);
}

