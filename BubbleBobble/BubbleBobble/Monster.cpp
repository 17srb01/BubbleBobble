#include "stdafx.h"
#include "Monster.h"
#include "Pickup.h"


Monster::Monster()
{
	noLevelCollision = true;
	setVelocity(0, 1);
}


Monster::~Monster()
{
}

void Monster::updateVelocity()
{
	if (!noLevelCollision)
	{
		//any change.
		//check for collision.
		gameData->getList(0).at(0)->collision(this);
		//move.
		rectangle.move(velocity);
	}
}

void Monster::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(2, temp);

	//pickup creation
	//something like...
	temp = new Pickup();
	gameData->add(5, temp);
}

void Monster::distanceLimitPassed()
{
	noLevelCollision = false;
}