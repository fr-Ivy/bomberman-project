#include "precomp.h"
#include "Valcom.h"
#include "map.h"
#include "player.h"
#include "Brick.h"
#include <iostream>


Valcom::Valcom(Surface* screen, Sprite* enemySprite, Map* map, Player* player, Game* game)
	: Enemy(screen, enemySprite, map, player, game)
{
}

void Valcom::checkBrickCollision()
{
	BrickCollision = false;
	for (int i = game->currentLevel * brickCount; i < brickCount * game->currentLevel + brickCount; i++)
	{
		//check coll for each dir
		if (brick[i] && brick[i]->checkCollision(tx - cameraX, ty, SPRITE_SIZE))
		{
			BrickCollision = true;
		}
	}
}

bool Valcom::checkCorners(int x1, int y1, int x2, int y2)
{
	return map->CheckCollision(x1, y1) && map->CheckCollision(x2, y2);
}

void Valcom::BackToTile()
{
	int px = static_cast<int>(tx);
	cout << px << endl;

	if (px % TILE_SIZE >= 32)
	{
		px = (px / TILE_SIZE) * TILE_SIZE + TILE_SIZE;

	}
	else
	{
		px = (px / TILE_SIZE) * TILE_SIZE;

	}
	tx = static_cast<float>(px);

	int py = static_cast<int>(ty);
	cout << py << endl;

	if (py % TILE_SIZE >= 32)
	{
		py = (py / TILE_SIZE) * TILE_SIZE + TILE_SIZE;

	}
	else
	{
		py = (py / TILE_SIZE) * TILE_SIZE;

	}
	ty = static_cast<float>(py);
}

void Valcom::move(float deltaTime)
{
	deltaTime /= 1000.0f;
	vX = 250.0f * deltaTime;
	vY = 250.0f * deltaTime;
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

	int left = static_cast<int>(tx - cameraX);
	int right = left + SPRITE_SIZE - 1;
	int top = static_cast<int>(ty);
	int bottom = top + SPRITE_SIZE - 1;

	checkBrickCollision();

	switch (currDirection)
	{
	case Direction::UP:
		if (!checkCorners(left, top, right, top) && !BrickCollision)
		{
			ty -= vY;
		}
		else if (checkCorners(left, top, right, top) || BrickCollision)
		{
			BackToTile();
			vY = -vY;
		}
		break;
	case Direction::DOWN:
		if(!checkCorners(left, bottom, right, bottom) && !BrickCollision)
		{
			ty += vY;
		}
		else if (checkCorners(left, bottom, right, bottom) || BrickCollision)
		{
			BackToTile();
			vY = -vY;
		}
		break;
	case Direction::LEFT:
		if (!checkCorners(left, top, left, bottom) && !BrickCollision)
		{
			tx -= vX;
		}
		else if (checkCorners(left, top, left, bottom) || BrickCollision)
		{
			BackToTile();
			vX = -vX;
		}
		break;
	case Direction::RIGHT:
		if (!checkCorners(right, top, right, bottom) && !BrickCollision)
		{
			tx += vX;
		}
		else if (checkCorners(right, top, right, bottom) || BrickCollision)
		{
			BackToTile();
			vX = -vX;
		}
		break;
	}

	x = tx;
	y = ty;
}

