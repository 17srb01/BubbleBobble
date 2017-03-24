#include "stdafx.h"
#include "Level.h"
#include <iostream>
#include <fstream>


Level::Level()
{
}


Level::Level(std::string id)
{
	name = id;
	if (!texture.loadFromFile("../textures/Levels/" + name + "/" + name + "base.png"))
		std::cout << "Failed to load " << "../textures/Levels/" << name << "/" << name << "base.png";
	bitmapMaker();
}


Level::~Level()
{
}

bool Level::update()
{
	enemyCheck();
	time();
	distance();
	return life;
}

void Level::timeLimitPassed()
{
	levelEnd();
	gameData->getList(0).at(1)->levelEnd();

	std::vector<GameObject *> players = gameData->getList(1);
	for (int i = 0; i < players.size(); i++)
	{
		players.at(i)->levelEnd();
	}
}

void Level::distanceLimitPassed()
{
	if (offTop())
	{
		death();
		gameData->getList(0).at(1)->levelStart();
	}
}

void Level::levelEnd()
{
	setVelocity(0, -1);
	setPedometerLimit(window->getSize().y);
	startPedometer();

	std::string newName = name.substr(0, 4);
	int newNumber = std::stoi(name.substr(5)) + 1;
	newName += newNumber;

	GameObject *nextLevel = new Level(newName);
	gameData->add(0, nextLevel);
}

void Level::levelStart()
{
	setVelocity(0, 0); 
	std::vector<GameObject *> players = gameData->getList(1);
	for (int i = 0; i < players.size(); i++)
	{
		players.at(i)->levelStart();
	}
}

void Level::death()
{
	life = false;
	GameObject *temp = this;
	gameData->addToKillList(0, temp);
}

void Level::collision(GameObject *other)
{
	if (velocity.x || velocity.y)
	{
		std::vector<int> horizontal, vertical;

		int multiplierX, multiplierY = 1;
		sf::RectangleShape rect = other->getRectangle();
		sf::RectangleShape moving = rect;
		moving.move(other->getVelocity());

		sf::Vector2f center;
		sf::Vector2i corner;
		float width, height;
		width = moving.getLocalBounds().width;
		height = moving.getLocalBounds().height;
		center.x = moving.getGlobalBounds().left + width / 2;
		center.y = moving.getGlobalBounds().top + height / 2;

		if (other->getVelocity().x < 0)
			multiplierX = -1;
		if (other->getVelocity().y < 0)
			multiplierY = -1;

		corner.x = center.x + multiplierX * width / 2;
		corner.y = center.y + multiplierY * height / 2;

		if (std::floor(moving.getGlobalBounds().left / 8) != std::floor(rect.getGlobalBounds().left / 8))
		{
			for (int i = 0; i < height / 8; i++)
			{
				horizontal.push_back(bitmap[corner.x][corner.y + multiplierY * i]);
			}
		}

		if (std::floor(moving.getGlobalBounds().top / 8) != std::floor(rect.getGlobalBounds().top / 8))
		{
			for (int i = 0; i < height / 8; i++)
			{
				vertical.push_back(bitmap[corner.x + -1 * multiplierX * i][corner.y]);
			}
		}

		//Interpret.
		for (int i = 0; i < horizontal.size(); i++)
		{
			enum type { Wall = 1 };
			switch (horizontal.at(i))
			{
			case Wall:
				other->velocityToNextGridLine(true);
			}
		}
		for (int i = 0; i < vertical.size(); i++)
		{
			enum type { Floor = 2 };
			switch (horizontal.at(i))
			{
			case Floor:
				if (other->getVelocity().y < 0)
					other->velocityToNextGridLine(false); 
			}
		}

		if (other->getName().find("monster"))
		{

		}

	}
}

void Level::bitmapMaker()
{
	std::fstream input;
	input.open("../textures/Levels/" + name + "/" + name + "base.txt");
	if (input.is_open())
	{
		int incrementX = 0;
		int incrementY = 0;
		while (!input.eof() && incrementX < BITMAP_WIDTH)
		{
			input >> bitmap[incrementX][incrementY];
			incrementY++;
			if (incrementY >= BITMAP_HEIGHT)
			{
				incrementX++;
				incrementY = 0;
			}
		}
	}
	else
	{
		std::cout << "Failed to load " << "../textures/Levels/" << name << "/" << name << "base.txt";
	}
}

void Level::enemyCheck()
{
	//if no enemies left
	if (gameData->exist(3))
	{
		setTimeLimit(sf::seconds(5));
		startClock();
	}
}