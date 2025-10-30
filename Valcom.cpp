#include "precomp.h"
#include "Valcom.h"
#include "map.h"
#include <iostream>


Valcom::Valcom(Surface* screen, Sprite* enemySprite, Map& map, Player& player1, Player& player2, Game* game, int points)
	: Enemy(screen, enemySprite, map, player1, player2, game, points)
{
}

void Valcom::Move(float const deltaTime)
{
	vX = speed * deltaTime;
	vY = speed * deltaTime;
	tx = x;
	ty = y;

	int changeDirection = rand() % 100;
	if (changeDirection >= 90)
	{
		int chosenNumber = rand() % 4;
		if (static_cast<int>(x) % TILE_SIZE == 0 && static_cast<int>(y) % TILE_SIZE == 0)
		{
			currDirection = static_cast<Direction>(chosenNumber);
		}
	}

	int left = static_cast<int>(tx);
	int right = left + SPRITE_SIZE - 1;
	int top = static_cast<int>(ty);
	int bottom = top + SPRITE_SIZE - 1;

	CheckBrickCollision(static_cast<int>(tx), static_cast<int>(ty));

	switch (currDirection)
	{
	case Direction::UP:
		if (!CheckCorners(left, top, right, top) && !brickCollision && !BombCollision())
		{
			ty -= vY;
		}
		else if (CheckCorners(left, top, right, top) || brickCollision || BombCollision())
		{
			BackToTile();
			vY = -vY;
		}
		break;
	case Direction::DOWN:
		if(!CheckCorners(left, bottom, right, bottom) && !brickCollision && !BombCollision())
		{
			ty += vY;
		}
		else if (CheckCorners(left, bottom, right, bottom) || brickCollision || BombCollision())
		{
			BackToTile();
			vY = -vY;
		}
		break;
	case Direction::LEFT:
		if (!CheckCorners(left, top, left, bottom) && !brickCollision && !BombCollision())
		{
			tx -= vX;
		}
		else if (CheckCorners(left, top, left, bottom) || brickCollision || BombCollision())
		{
			BackToTile();
			vX = -vX;
		}
		break;
	case Direction::RIGHT:
		if (!CheckCorners(right, top, right, bottom) && !brickCollision && !BombCollision())
		{
			tx += vX;
		}
		else if (CheckCorners(right, top, right, bottom) || brickCollision || BombCollision())
		{
			BackToTile();
			vX = -vX;
		}
		break;
	case Direction::NONE:
		break;
	}

	x = tx;
	y = ty;
	WalkingAnitmation(deltaTime);
}

