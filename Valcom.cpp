#include "precomp.h"
#include "Valcom.h"
#include "map.h"
#include "player.h"
#include "Brick.h"
#include <iostream>


Valcom::Valcom(Surface* screen, Sprite* enemySprite, Map* map, Player* player1, Player* player2, Game* game)
	: Enemy(screen, enemySprite, map, player1, player2, game)
{
}

void Valcom::CheckBrickCollision()
{
	BrickCollision = false;
	for (int i = game->currentLevel * brickCount; i < brickCount * game->currentLevel + brickCount; i++)
	{
		//check coll for each dir
		if (brick[i] && brick[i]->checkCollision(0, tx - cameraX2, ty, SPRITE_SIZE))
		{
			BrickCollision = true;
		}
	}
}

bool Valcom::CheckCorners(int const x1, int const y1, int const x2, int const y2) const
{
	return map->CheckCollision(0, x1, y1) && map->CheckCollision(0, x2, y2);
}

void Valcom::BackToTile()
{
	int px = static_cast<int>(tx);
	//cout << px << endl;

	if (px % TILE_SIZE >= 32)
	{
		px = px / TILE_SIZE * TILE_SIZE + TILE_SIZE;

	}
	else
	{
		px = px / TILE_SIZE * TILE_SIZE;

	}
	tx = static_cast<float>(px);


	int py = static_cast<int>(ty);
	//cout << py << endl;

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

void Valcom::Move(float const deltaTime)
{
	cameraX2 = map->getCamera(0);
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

	int left = static_cast<int>(tx - cameraX2);
	int right = left + SPRITE_SIZE - 1;
	int top = static_cast<int>(ty);
	int bottom = top + SPRITE_SIZE - 1;

	CheckBrickCollision();

	switch (currDirection)
	{
	case Direction::UP:
		if (!CheckCorners(left, top, right, top) && !BrickCollision)
		{
			ty -= vY;
		}
		else if (CheckCorners(left, top, right, top) || BrickCollision)
		{
			BackToTile();
			vY = -vY;
		}
		break;
	case Direction::DOWN:
		if(!CheckCorners(left, bottom, right, bottom) && !BrickCollision)
		{
			ty += vY;
		}
		else if (CheckCorners(left, bottom, right, bottom) || BrickCollision)
		{
			BackToTile();
			vY = -vY;
		}
		break;
	case Direction::LEFT:
		if (!CheckCorners(left, top, left, bottom) && !BrickCollision)
		{
			tx -= vX;
		}
		else if (CheckCorners(left, top, left, bottom) || BrickCollision)
		{
			BackToTile();
			vX = -vX;
		}
		break;
	case Direction::RIGHT:
		if (!CheckCorners(right, top, right, bottom) && !BrickCollision)
		{
			tx += vX;
		}
		else if (CheckCorners(right, top, right, bottom) || BrickCollision)
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
}

