#include "Level.h"

#include <fstream>
#include <iostream>
#include <algorithm>

#include <Bengine/Errors.h>
#include <Bengine/ResourceManager.h>

#include <fstream>

Level::Level(const std::string& fileName)
{

	std::ifstream file(fileName);

	// Error Checking
	if (file.fail()) {
		Bengine::fatalError("Failed to open " + fileName);
	}

	//Throw away the first string in temp
	std::string tmp;

	file >> tmp >> _numHumans;

	std::getline(file, tmp); //Throw away the rest of the first line
	while (std::getline(file, tmp)) {
		_levelData.push_back(tmp);
	}

	std::reverse(_levelData.begin(), _levelData.end());

	_spriteBatch.init();
	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color(255, 255, 255, 255);

	// Render all the tiles
	for (unsigned int y = 0; y < _levelData.size(); ++y) {
		for (unsigned int x = 0; x < _levelData[y].size(); ++x) {
			// Grab the tile
			char tile = _levelData[y][x];

			// Get dest rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
			// Process the tile
			switch (tile) {
				case 'L':
					// _spriteBatch.draw(destRect,
					// 				  uvRect,
					// 				  Bengine::ResourceManager::getTexture("Textures/r.png").id,
					// 				  0.0f,
					// 				  color);
					// break;
				case 'G':
					// _spriteBatch.draw(destRect,
					// 				  uvRect,
					// 				  Bengine::ResourceManager::getTexture("Textures/g.png").id,
					// 				  0.0f,
					// 				  color);
					// break;
				case 'R':
					_spriteBatch.draw(destRect,
									  uvRect,
									  Bengine::ResourceManager::getTexture("Textures/tile1.png").id,
									  0.0f,
									  color);
					break;
				case '@':
					_levelData[y][x] = '.'; /// So we dont collide with with an @
					_startPlayerPos.x = (float)(x * TILE_WIDTH);
					_startPlayerPos.y = (float)(y * TILE_WIDTH);
					break;
				case 'Z':
					_levelData[y][x] = '.'; /// So we dont collide with with a Z
					_zombieStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					break;
				case '.':
					break;
				default:
					std::printf("Unexpected symbol %c at (%d,%d)\n", tile, x, y);
			}
		}
	}

	_spriteBatch.end();


}


Level::~Level()
{
}

void Level::draw() {
	_spriteBatch.renderBatch();
}
