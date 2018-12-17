#include "ZombieGame.h"

#include <Bengine/Bengine.h>
#include <Bengine/Timing.h>
#include <Bengine/Errors.h>
#include <random>
#include <ctime>
#include <algorithm>

#include <SDL/SDL.h>
#include <iostream>

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;
const float PLAYER_SPEED = 5.0f;

const float CAMERA_SCALE = 1.0f;

ZombieGame::ZombieGame() {
	// Empty
}

ZombieGame::~ZombieGame() {
	for (unsigned int i = 0; i < _levels.size(); ++i) {
		delete _levels[i];
	}

	for (unsigned int i = 0; i < _humans.size(); ++i) {
		delete _humans[i];
	}

	for (unsigned int i = 0; i < _zombies.size(); ++i) {
		delete _zombies[i];
	}
}

void ZombieGame::run() {
	initSystems();

	initLevel();

	gameLoop();

}

void ZombieGame::initSystems() {
	Bengine::init();

	_window.create("Zombie Game", _screenWidth, _screenHeight, 0);

	initShaders();

	_agentSpriteBatch.init();

	_camera.init(_screenWidth, _screenHeight);
}

void ZombieGame::initLevel() {
	// Level 1
	_levels.push_back(new Level("Levels/level1.txt")); 
	_currentLevel = 0;

	_player = new Player;
	_player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager, &_camera, &_bullets);

	_humans.push_back(_player);

	std::mt19937 randomEngine;
	std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

	// Add all the random humnas
	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); ++i) {
		_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine)  * TILE_WIDTH);
		_humans.back()->init(HUMAN_SPEED, pos);
	}

	// Add all the zombies
	const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombieStartPositions();
	for (unsigned int i = 0; i < zombiePositions.size(); ++i) {
		_zombies.push_back(new Zombie);
		_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	// Setup the players guns
	const float BULLET_SPEED = 20.0f;
	_player->addGun(new Gun("Magnum",  30, 1,  0.1f, 30, BULLET_SPEED));
	_player->addGun(new Gun("Shotgun", 60, 8, 0.4f, 4,  BULLET_SPEED));
	_player->addGun(new Gun("MP5",     5,  1,  0.05f, 20, BULLET_SPEED));

}

void ZombieGame::initShaders() {
	_textureProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");
	_textureProgram.linkShaders();
}

void ZombieGame::gameLoop() {

	const float DESIRED_FPS = 60.0f;
	const int MAX_PHYSICS_STEPS = 6;

	Bengine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(DESIRED_FPS);

	_camera.setScale(CAMERA_SCALE);

	const float MS_PER_SECOND = 1000.0f;
	const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f;

	float previousTicks = (float)SDL_GetTicks();

	while (_gameState == GameState::PLAY) {
		fpsLimiter.begin();

		float newTicks = (float)SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		checkVictory();

		_inputManager.update();

		processInput();

		int i = 0;
		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
			updateAgents(deltaTime);
			updateBullets(deltaTime);
			totalDeltaTime -= deltaTime;

			i++;
		}
		
		_camera.setPosition(_player->getPosition());
		_camera.update();

		drawGame();
		_fps = fpsLimiter.end();
		//std::cout << _fps << "\r";
	}
}

void ZombieGame::updateAgents(float deltaTime) {
	// Update all humans
	for (unsigned int i = 0; i < _humans.size(); ++i) {
		_humans[i]->update(_levels[_currentLevel]->getLevelData(), 
			_humans, 
			_zombies, 
			deltaTime);
	}

	// Update all zombies
	for (unsigned int i = 0; i < _zombies.size(); ++i) {
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(), 
			_humans, 
			_zombies, 
			deltaTime);
	}

	// update Zombie collisions
	for (unsigned int i = 0; i < _zombies.size(); ++i) {

		// Collide with other zombies
		for (unsigned int j = i + 1; j < _zombies.size(); ++j) {
			_zombies[i]->collideWithAgent(_zombies[j]);
		}

		// Collide with humans
		for (unsigned int j = 1; j < _humans.size(); ++j) {
			if (_zombies[i]->collideWithAgent(_humans[j])) {
				// Add the new zombie
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition());

				// Delete the human
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}

		// Collide with player
		if (_zombies[i]->collideWithAgent(_player)) { // _humans[0] is the player
			std::printf("\n*** You Lose ***\nYou killed %d humans and %d zombies. There are %d/%d humans remaining.",
				_numHumansKilled,
				_numZombiesKilled,
				_humans.size() - 1,
				_levels[_currentLevel]->getNumHumans());
			_gameState = GameState::EXIT;
			Bengine::fatalError("");
		}
	}

	// update Human collisions
	for (unsigned int i = 0; i < _humans.size(); ++i) {
		// Collide with other humans
		for (unsigned int j = i + 1; j < _humans.size(); ++j) {
			_humans[i]->collideWithAgent(_humans[j]);
		}
	}

}

void ZombieGame::updateBullets(float deltaTime) {

	// Update and collide with world
	for (unsigned int i = 0; i < _bullets.size();) {
		// If update return true then bullet collided with the wall
		if (_bullets[i].update(_levels[_currentLevel]->getLevelData(), deltaTime)) {
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else {
			i++;
		}
	}

	bool wasBulletremoved;

	// Collide with humans and zombies
	for (unsigned int i = 0; i < _bullets.size(); ++i) {
		wasBulletremoved = false;
		// Loop thorugh zombies
		for (unsigned int j = 0; j < _zombies.size();) {
			// Check collision
			if (_bullets[i].collideWithAgent(_zombies[j])) {
				// damage the zombie
				if (_zombies[j]->applyDamage(_bullets[i].getDamage())) {

					// if Zombie dies, remove him
					delete _zombies[j];
					_zombies[j] = _zombies.back();
					_zombies.pop_back();
					_numZombiesKilled++;
					printf("\nZombie Death Count: %d\nFriendly Death Count: %d\n", _numZombiesKilled, _numHumansKilled);
				}
				else {
					j++;
				}


				// Rremove the bullet
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				wasBulletremoved = true;
				i--; //Make sure we dont skip a bullet

				//Since the bullet died, no need to loop through any more zombies
				break;
			}
			else {
				j++;
			}
		}

		// Loop thorugh Humans
		if (!wasBulletremoved) {

			for (unsigned int j = 1; j < _humans.size(); ) {
				// Check collision
				if (_bullets[i].collideWithAgent(_humans[j])) {
					// damage human


					if (_humans[j]->applyDamage(_bullets[i].getDamage())) {

						// if Human dies, remove him
						delete _humans[j];
						_humans[j] = _humans.back();
						_humans.pop_back();

						_numHumansKilled++;
						printf("\nZombie Death Count: %d\nFriendly Death Count: %d\n", _numZombiesKilled, _numHumansKilled);
					}
					else {
						j++;
					}


					// Rremove the bullet
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					wasBulletremoved = true;
					i--; //Make sure we dont skip a bullet

						 //Since the bullet died, no need to loop through any more zombies
					break;
				}
				else {
					j++;
				}
			}
		}
	}

}

void ZombieGame::checkVictory() {
	// TODO: Supoort for multiple levels;
	// _currentLevel++; initLevel(...)
	// If all zombies are dead we win
	if (_zombies.empty()) {
		std::printf("\n*** You win ***\nYou killed %d humans and %d zombies. There are %d/%d humans remaining.",
			_numHumansKilled,
			_numZombiesKilled,
			_humans.size() - 1,
			_levels[_currentLevel]->getNumHumans());
		_gameState = GameState::EXIT;
		Bengine::fatalError("");
	}
}

void ZombieGame::processInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCords((float)evnt.motion.x, (float)evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}

}

void ZombieGame::drawGame() {
	//Set the base depth to 1.0
	glClearDepth(1.0);
	//CLear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Binding the shaders
	_textureProgram.use();

	// Draw Code Goes here
	glActiveTexture(GL_TEXTURE0);

	// Make sure the shader uses texture 0
	GLint textureUniform = _textureProgram.getUnifromLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// Grab the camera matrix
	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUnifromLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Draw the level
	_levels[_currentLevel]->draw();

	// Begin drawing agents
	_agentSpriteBatch.begin();

	const glm::vec2 agentDims(AGENT_RADIUS * 2.0f);

	// Draw the humans
	for (unsigned int i = 0; i < _humans.size(); ++i) {
		// Camera culling: Drawing humans if in view
		if (_camera.isBoxInView(_humans[i]->getPosition(), agentDims)) {
			_humans[i]->draw(_agentSpriteBatch);
		}
	}

	// Draw the zombies
	for (unsigned int i = 0; i < _zombies.size(); ++i) {
		// Camera culling: Drawing zombies if in view
		if (_camera.isBoxInView(_zombies[i]->getPosition(), agentDims)) {
			_zombies[i]->draw(_agentSpriteBatch);
		}
	}

	// Draw the bullets
	for (unsigned int i = 0; i < _bullets.size(); ++i) {
		// Camera culling: Drawing Bullets if in view
		if (_camera.isBoxInView(_bullets[i].getPosition(), agentDims)) {
			_bullets[i].draw(_agentSpriteBatch);
		}
	}

	_agentSpriteBatch.end();

	_agentSpriteBatch.renderBatch();

	// Unbind the textures
	_textureProgram.unuse();

	//Swap our buffer and draw everything to the screen
	_window.swapBuffer();
}
