#pragma once
#include "Human.h"
#include "Gun.h"
#include <Bengine/InputManager.h>
#include <Bengine/Camera2D.h>



class Player :
	public Human
{
public:
	Player();
	~Player();

	void init(float speed, 
		glm::vec2 pos, 
		Bengine::InputManager* inputManager, 
		Bengine::Camera2D* camera, 
		std::vector<Bullet>* bullets);

	void addGun(Gun* gun);

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies,
		float deltaTime) override;


private:
	Bengine::InputManager* _inputManager;
	std::vector<Bullet>* _bullets;

	std::vector<Gun*> _guns;
	int _currentGunIndex = -1;
	Bengine::Camera2D* _camera;
};

