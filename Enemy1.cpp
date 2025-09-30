#include "precomp.h"
#include "Enemy1.h"
#include "map.h"
#include "player.h"
#include "Brick.h"
#include <iostream>


Enemy1::Enemy1(Surface* screen, Sprite* enemySprite, Map* map, Player* player, Game* game)
	: Enemy(screen, enemySprite, map, player, game)
{
}

void Enemy1::move(float deltaTime)
{
	deltaTime /= 1000.0f;
	cameraX = map->getCamera();
	directionCountdown -= deltaTime;

	tx = x;
	ty = y;

	tx += vX * deltaTime;
	ty += vY * deltaTime;


	bool brickCollision = false;
	for (int i = game->currentLevel * brickCount; i < brickCount * game->currentLevel + brickCount; i++)
	{
		if (brick[i] && brick[i]->checkCollision(tx - cameraX, ty, SPRITE_SIZE))
		{
			brickCollision = true;
			break;
		}
	}

	if (tx > x)
	{
		if (!map->CheckCollision(tx - cameraX + SPRITE_SIZE - 1, y) &&
			!map->CheckCollision(tx - cameraX + SPRITE_SIZE - 1, y + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			x = tx;
		}
		else if ((map->CheckCollision(tx - cameraX + SPRITE_SIZE, y) &&
			map->CheckCollision(tx - cameraX, y + SPRITE_SIZE)) ||
			brickCollision)
		{
			if (directionCountdown <= 0.0f)
			{
				vX = -vX;
				directionCountdown = 0.5f;
			}
		}
	}
	else if (tx < x)
	{
		if (!map->CheckCollision(tx - cameraX, y) &&
			!map->CheckCollision(tx - cameraX, y + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			x = tx;
		}
		else if ((map->CheckCollision(tx - cameraX, y) &&
			map->CheckCollision(tx - cameraX, y + SPRITE_SIZE)) ||
			brickCollision)
		{
			if (directionCountdown <= 0.0f)
			{
				vX = -vX;
				directionCountdown = 0.5f;
			}
		}
	}

	if (ty > y)
	{
		if (!map->CheckCollision(x - cameraX, ty + SPRITE_SIZE - 1) &&
			!map->CheckCollision(x - cameraX + SPRITE_SIZE - 1, ty + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			y = ty;
		}
	}
	else if (ty < y)
	{
		if (!map->CheckCollision(x - cameraX, ty) &&
			!map->CheckCollision(x - cameraX + SPRITE_SIZE - 1, ty) &&
			!brickCollision)
		{
			y = ty;
		}
	}


	screenX = x - cameraX;
	//cout << x << ", " << y << endl;
	cout << vX << endl;
}



//check at each tile if it can change the direction, if it can't do nothing but if it can let a rand() decide
//rand() % 10
//if randomNumber == 1 change direction, else do nothing
