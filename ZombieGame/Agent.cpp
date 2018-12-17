#include "Agent.h"
#include <Bengine/ResourceManager.h>
#include "Level.h"
#include <algorithm>


Agent::Agent() {
	//Empty	
}


Agent::~Agent() {
	//Empty	
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData) {
	std::vector<glm::vec2>collideTilePosition;

	// Check the four corners
	// First corner
	checkTilePosition(levelData, 
		collideTilePosition, 
		_position.x,
		_position.y);

	// Second corner
	checkTilePosition(levelData, 
		collideTilePosition, 
		_position.x + AGENT_WIDTH, 
		_position.y);

	// Third corner
	checkTilePosition(levelData,
		collideTilePosition,
		_position.x,
		_position.y + AGENT_WIDTH);

	// Fourth corner
	checkTilePosition(levelData,
		collideTilePosition,
		_position.x + AGENT_WIDTH,
		_position.y + AGENT_WIDTH);

	if (collideTilePosition.size() == 0) {
		return false;
	}

	// Do the collisions
	for (unsigned int i = 0; i < collideTilePosition.size(); ++i) {
		collideWithTile(collideTilePosition[i]);
	}
	
	return true;
}

bool Agent::collideWithAgent(Agent* agent) {

	const float MIN_DIST = AGENT_RADIUS * 2.0f;

	glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);
	float collisionDepth = MIN_DIST - distance;
	if (collisionDepth > 0) {
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;
		_position += collisionDepthVec / 2.0f;
		agent->_position -= collisionDepthVec / 2.0f;

		return true;
	}

	return false;
}

void Agent::draw(Bengine::SpriteBatch & _spriteBatch) {

	static int textureID = Bengine::ResourceManager::getTexture("Textures/circle.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	_spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}

bool Agent::applyDamage(float damage)
{
	_health -= damage;
	if (_health <= 0) {
		return true;
	}
	return false;
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData, 
	std::vector<glm::vec2>& collideTilePosition, 
	float x, 
	float y) 
{
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
									  floor(y / (float)TILE_WIDTH));

	// If we are outside the world just return
	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].size() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size()) {
		return;
	}
	if (levelData[(unsigned int)cornerPos.y][(unsigned int)cornerPos.x] != '.') {
		collideTilePosition.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

// AABB Collision
void Agent::collideWithTile(glm::vec2 tilePos) {
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DIST = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerAgentPos = _position + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerAgentPos - tilePos;

	float xDepth = MIN_DIST - abs(distVec.x);
	float yDepth = MIN_DIST - abs(distVec.y);

	// If this is true, we are colliding
	if (xDepth > 0 && yDepth > 0) {
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			if (distVec.x < 0) {
				_position.x -= xDepth;
			} else {
				_position.x += xDepth;
			}
		}

		else {
			if (distVec.y < 0) {
				_position.y -= yDepth;
			} else {
				_position.y += yDepth;
			}
		}
	}
}
