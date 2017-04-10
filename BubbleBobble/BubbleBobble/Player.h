#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	Player(std::string);
	~Player();
	void update();
	void collideWith();
	void collided(GameObject *);
	void pickedUp(GameObject *);
	void levelEnd();
	void levelStart();
	void levelPlay();
	void levelTransition();
	void death();
	void timeLimitPassed();
	void moveLeft();
	void moveRight();
	void stopHorizontalVelocity();
	void stopVerticalVelocity();
	void jump();
	void jumping();
	int getDirection();
private: 
	sf::Clock jumpTimer;
	bool jump_m;
	int direction;
};

