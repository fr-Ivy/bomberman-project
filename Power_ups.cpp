#include "precomp.h"
#include "Power_ups.h"
#include "Player.h"
#include "Map.h"
#include "Brick.h"
#include <iostream>

Power_ups::Power_ups(Surface* screen, Sprite* powerUpSprite, Player* player1, Player* player2, Bomb* bomb1, Bomb* bomb2, Map* map)
	: player1(player1), player2(player2), screen(screen), bomb1(bomb1), bomb2(bomb2), map(map)
{
	this->powerUpSprite = powerUpSprite;
}

Power_ups::~Power_ups()
{
}

void Power_ups::ChoosePos(int level)
{
	do
	{
		chosenBrick = rand() % brickCount + level * brickCount;
	} while (!brick[chosenBrick]);

	x = static_cast<float>(brick[chosenBrick]->getX());
	y = static_cast<float>(brick[chosenBrick]->getY());
	//cout << chosenBrick << endl;
}

void Power_ups::Draw(Surface* surface, int camera)
{
	if (powerUpSprite)
	{
		powerUpSprite->Draw(surface, static_cast<int>(x - map->getCamera(camera)), static_cast<int>(y));
	}
}

bool Power_ups::Collision1()
{
	if (player1->checkAABBCollision(x + 2, y + 2, SPRITE_SIZE - 4))
	{
		cout << "hit" << endl;
		return true;
	}
	return false;
}

bool Power_ups::Collision2()
{
	if (player2->checkAABBCollision(x + 2, y + 2, SPRITE_SIZE - 4))
	{
		cout << "hit" << endl;
		return true;
	}
	return false;
}

void Power_ups::Power()
{
}
