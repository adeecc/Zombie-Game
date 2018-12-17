#include "Bullet.h"
#include <Bengine/ResourceManager.h>

#include "Human.h"
#include "Zombie.h"
#include "Level.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed) :
	_position(position),
	_direction(direction),
	_damage(damage),
	_speed(speed)
{
}


Bullet::~Bullet()
{
}

bool Bullet::update(const std::vector<std::string>& levelData, float deltaTime) {
	_position += _direction * _speed * deltaTime;
	return collideWithWorld(levelData);
}

void Bullet::draw(Bengine::SpriteBatch & spriteBatch) {
	glm::vec4 destRect(_position.x + BULLET_RADIUS, 
					   _position.y + BULLET_RADIUS, 
						BULLET_RADIUS * 2, 
						BULLET_RADIUS * 2);

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	Bengine::ColorRGBA8 color(60, 60, 60, 255);

	spriteBatch.draw(destRect,
		uvRect,
		Bengine::ResourceManager::getTexture("Textures/circle.png").id,
		0.0f,
		color);


}

bool Bullet::collideWithAgent(Agent* agent)
{
	const float MIN_DIST = AGENT_RADIUS + BULLET_RADIUS;

	glm::vec2 centerPosA = _position;
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);
	float collisionDepth = MIN_DIST - distance;
	if (collisionDepth > 0) {
		return true;
	}

	return false;
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = (glm::i32)floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = (glm::i32)floor(_position.y / (float)TILE_WIDTH);

	// If we are outside world, then collide
	if (gridPosition.x < 0 || (unsigned int)gridPosition.x >= levelData[0].size() ||
		gridPosition.y < 0 || (unsigned int)gridPosition.y >= levelData.size()) {
		return true;
	}

	return (levelData[gridPosition.y][gridPosition.x] != '.');
}
