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

void Enemy1::checkBrickCollision()
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

void Enemy1::moveHorizontal(Direction currDir)
{
	if (currDir == Direction::RIGHT ) //right
	{
		int rightCorner = static_cast<int>(tx - cameraX) + SPRITE_SIZE - 1;
		int bottomCorner = static_cast<int>(ty) + SPRITE_SIZE - 1;

		checkBrickCollision();
		if (!map->CheckCollision(rightCorner, ty) &&
			!map->CheckCollision(rightCorner, bottomCorner) &&
			!BrickCollision)
		{
			x = tx;
		}

		else if ((map->CheckCollision(rightCorner, ty) &&
			map->CheckCollision(rightCorner,bottomCorner)) ||
			BrickCollision)
		{
			if (directionCountdown <= 0.0f)
			{
				cout << "hit" << endl;
				vX = -vX;
				BackToTile();
				directionCountdown = 0.5f;
			}
		}
	}
	else if (currDir == Direction::LEFT) //left 
	{
		int leftCorner = static_cast<int>(tx - cameraX);
		int bottomCorner = static_cast<int>(ty) + SPRITE_SIZE - 1;

		checkBrickCollision();
		if (!map->CheckCollision(leftCorner, ty) &&
			!map->CheckCollision(leftCorner, bottomCorner) &&
			!BrickCollision)
		{
			x = tx;
		}

		else if ((map->CheckCollision(leftCorner, ty) &&
			map->CheckCollision(leftCorner, bottomCorner)) ||
			BrickCollision)
		{
			if (directionCountdown <= 0.0f)
			{
				cout << "hit" << endl;
				vX = -vX;
				BackToTile();
				directionCountdown = 0.5f;
			}
		}
	}
}

void Enemy1::moveVertical(Direction currDir)
{
	if (currDir == Direction::DOWN) //down
	{
		int leftCorner = static_cast<int>(tx - cameraX);
		int rightCorner = static_cast<int>(tx - cameraX) + SPRITE_SIZE - 1;
		int bottomCorner = static_cast<int>(ty) + SPRITE_SIZE - 1;

		checkBrickCollision();
		if (!map->CheckCollision(leftCorner, ty + SPRITE_SIZE) &&
			!map->CheckCollision(rightCorner, ty + SPRITE_SIZE) &&
			!BrickCollision)
		{
			y = ty;
		}

		else if ((map->CheckCollision(leftCorner, bottomCorner) &&
			map->CheckCollision(rightCorner, bottomCorner)) ||
			BrickCollision)
		{
			if (directionCountdown <= 0.0f)
			{
				cout << "hit" << endl;
				vY = -vY;
				directionCountdown = 0.5f;
				BackToTile();
			}
		}
	}
	else if (currDir == Direction::UP) //up
	{
		int leftCorner = static_cast<int>(tx - cameraX);
		int rightCorner = static_cast<int>(tx - cameraX) + SPRITE_SIZE - 1;

		checkBrickCollision();

		if ((map->CheckCollision(leftCorner, ty) &&
			map->CheckCollision(rightCorner, ty)) ||
			BrickCollision)
		{
			if (directionCountdown <= 0.0f)
			{
				cout << "hit" << endl;
				vY = -vY;
				BackToTile();
				directionCountdown = 0.5f;
			}
		}
		else if (!map->CheckCollision(leftCorner, ty) &&
			!map->CheckCollision(rightCorner, ty) &&
			!BrickCollision)
		{
			y = ty;
		}
		//cout << "TopLeft hit: " << (topLeft ? "true" : "false") << endl;
		//cout << "topRight hit: " << (topRight ? "true" : "false") << endl;
	}
}

void Enemy1::BackToTile()
{
	int px = static_cast<int>(tx);
	px = px / TILE_SIZE * TILE_SIZE;
	cout << px << endl;
	tx = static_cast<float>(px);
	int py = static_cast<int>(ty);
	py = py / TILE_SIZE * TILE_SIZE;
	cout << py << endl;
	ty = static_cast<float>(py);
}

void Enemy1::move(float deltaTime)
{
	screen->Line(x + TILE_SIZE / 2 - cameraX, y + TILE_SIZE / 2, x + direction[currDir].x - cameraX + TILE_SIZE / 2, y + direction[currDir].y + TILE_SIZE / 2, 255);
	deltaTime /= 1000.0f;
	cameraX = map->getCamera();
	directionCountdown -= deltaTime;

	tx = x;
	ty = y;

	tx += vX * deltaTime;
	ty += vY * deltaTime;
	/*int px = static_cast<int>(x) / TILE_SIZE;
	int py = static_cast<int>(y) / TILE_SIZE;
	cout << px << ", " << py << endl;
	cout << x / 64.0f << ", " << y / 64.0f << endl;
	*/

	//if (static_cast<float>(px) == x / 64.0f && static_cast<float>(py) == y / 64.0f)
	//{
	/*if (tx > x || tx < x)
	{
		int changeDirection = rand() % 10;
		cout << changeDirection << endl;
		if (changeDirection == 9)
		{
			int choosenDirection = (rand() % 2) + 2;
			vY = direction[choosenDirection].y;
			cout << choosenDirection << endl;
		}
	}

	if (ty > y || ty < y)
	{
		int changeDirection = rand() % 10;
		cout << changeDirection << endl;
		if (changeDirection == 9)
		{
			int choosenDirection = rand() % 2;
			vX = direction[choosenDirection].x;
			cout << choosenDirection << endl;
		}
	}
	*/
	//}


	//cout << static_cast<int>(x) << ", " << static_cast<int>(y) << endl;

	if (static_cast<int>(x) % TILE_SIZE == 0 && static_cast<int>(y) % TILE_SIZE == 0)
	{
		int changeDirection = rand() % 10;
		//cout << changeDirection << endl;
		if (changeDirection == 9)
		{
			Direction choosenDirection = (Direction)(rand() % 4);
			vX = direction[choosenDirection].x;
			vY = direction[choosenDirection].y;
			currDir = choosenDirection;
			cout << choosenDirection << endl;
		}
	}



	moveHorizontal(currDir);
	moveVertical(currDir);

	screenX = x - cameraX;
	//cout << x << ", " << y << endl;
	//cout << vX << endl;
}
