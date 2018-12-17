#pragma once

#include <Bengine/Bengine.h>
#include <Bengine/Window.h>
#include <Bengine/Camera2D.h>
#include <Bengine/GLSLProgram.h>
#include <Bengine/InputManager.h>
#include <Bengine/SpriteBatch.h>

#include "Level.h"
#include "Player.h"
#include "Zombie.h"
#include "Gun.h"


enum class GameState {
	PLAY,
	EXIT
};

class ZombieGame
{
public:
	ZombieGame();
	~ZombieGame();

	/// Runs the game
	void run();

private:
	/// Initializes the core systems
	void initSystems();

	/// Initializes the level and sets up everything
	void initLevel();

	/// Initializes the shaders
	void initShaders();

	/// Main Game Loop for the program
	void gameLoop();

	/// Updates all agents
	void updateAgents(float deltaTime);

	/// Updates all bullets
	void updateBullets(float deltaTime);

	/// Checks the victory condiiton
	void checkVictory();

	/// Handles input Processing
	void processInput();

	/// Renders the game
	void drawGame();

	/// Member Variables
	Bengine::Window _window; ///< The Game Window

	Bengine::GLSLProgram _textureProgram; ///< The Shader Program

	Bengine::InputManager _inputManager; ///< Handles Input

	Bengine::Camera2D _camera; ///< Main Camera

	Bengine::SpriteBatch _agentSpriteBatch; ///< draws all agents

	std::vector<Level*> _levels; ///< Vector of all levels

	int _screenWidth = 1024;
	int _screenHeight = 720;

	float _fps = 0;

	int _currentLevel;

	Player* _player = nullptr;
	std::vector<Human*> _humans; ///< vector of all humans
	std::vector<Zombie*> _zombies; ///< vector of all zombies
	std::vector<Bullet> _bullets; ///< vector of all bullets

	int _numHumansKilled = 0; ///< Humnas killed by player
	int _numZombiesKilled = 0; ///< Zombies killed by player

	GameState _gameState = GameState::PLAY;
};


