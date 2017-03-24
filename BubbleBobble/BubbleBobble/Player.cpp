#include "stdafx.h"
#include "Player.h"
#include "Skel_Monsta.h"


Player::Player()
{

}


Player::~Player()
{
}

void Player::updateVelocity()
{
	if (levelTransition)
	{
		//move to corner
		sf::Vector2f corner;

		corner.y = 8 * 23;
		if (name == "Player2")
			corner.x = 8 * 29;
		else
			corner.x = 8;

		sf::Vector2f player;
		player.x = rectangle.getGlobalBounds().left;
		player.y = rectangle.getGlobalBounds().top;
		float differenceX = player.x - corner.x;
		float differenceY = player.y - corner.y;

		float angle = std::atan(differenceY / differenceX);

		velocity.x = cos(angle) * 2;
		velocity.y = sin(angle) * 2;
	}
	else
	{
		//standard update.
		gameData->getList(0).at(0)->collision(this);
		rectangle.move(velocity);
	}
}

void Player::levelEnd()
{
	levelTransition = true;
	//change animation.
}

void Player::levelStart()
{
	levelTransition = false;
	setTimeLimit(sf::seconds(30));
	startClock();
	//change animation.
}

void Player::timeLimitPassed()
{
	//Show hurry up text?
	//Begin pursuit of skel monsta.
	GameObject *skelMonsta = new Skel_Monsta();
	gameData->add(2, skelMonsta);
}

//player.pickup()
void Player::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(1, temp);
}