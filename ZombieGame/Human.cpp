#include "Human.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

Human::Human() {
	//Empty	
}


Human::~Human() {
	//Empty	
}

void Human::init(float speed, glm::vec2 pos) {

	static std::mt19937 randomEngine;
	static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

	_health = 20;
	_color = Bengine::ColorRGBA8(245, 93, 62, 255);
	_speed = speed;
	_position = pos;
	

	// Get random Direction
	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));

	// Make sure direction isn't zero
	if (_direction.length() == 0) glm::vec2(1.0f, 0.0f);

	_direction = glm::normalize(_direction);

}

void Human::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	float deltaTime)
{
	static std::mt19937 randomEngine;
	static std::uniform_real_distribution<float> randRotate(-0.2f, 0.2f);

	_position += _direction * _speed * deltaTime;

	// Randomly change direction every 20 frames
	if (_frames == 20) {
		_direction = glm::rotate(_direction, randRotate(randomEngine));
		_frames = 0;
	} else {
		_frames++;
	}

	if (collideWithLevel(levelData)) {
		_direction = glm::rotate(_direction, randRotate(randomEngine));
	}
}
