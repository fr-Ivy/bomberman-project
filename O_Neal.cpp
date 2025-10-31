#include "precomp.h"
#include "O_Neal.h"

#include <iostream>

#include "Player.h"


O_Neal::O_Neal(Surface* screen, Sprite* enemySprite, Map& map, Player& player1, Player& player2, Game* game, int points)
	: Enemy(screen, enemySprite, map, player1, player2, game, points)
{
}

//void Enemy::CheckBrickCollision(int x, int y)
//{
//	brickCollision = false;
//	for (int i = game->currentLevel * brickCount; i < brickCount * game->currentLevel + brickCount; i++)
//	{
//		//check collision for each dir
//		if (brick[i] && brick[i]->checkCollision(x, y, SPRITE_SIZE))
//		{
//			brickCollision = true;
//			cout << "hit" << endl;
//		}
//	}
//}

void O_Neal::Move(float deltaTime)
{
	int changeStatus = rand() % 100;
	if (changeStatus >= 70)
	{
		int chosenNumber = rand() % 2;
		if (static_cast<int>(x) % TILE_SIZE == 0 && static_cast<int>(y) % TILE_SIZE == 0)
		{
			currStatus = static_cast<status>(chosenNumber);
		}
	}

	switch (currStatus)
	{
	case status::IDLE:
		Idle(deltaTime);
		//cout << "IDLE\n";
		break;
	case status::CHASE:
		Chase(deltaTime);
		//cout << "CHASE\n";
		break;
	}
}

void O_Neal::Walking(float deltaTime)
{
	vX = speed * deltaTime;
	vY = speed * deltaTime;
	tx = x;
	ty = y;

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
		if (!CheckCorners(left, bottom, right, bottom) && !brickCollision && !BombCollision())
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


void O_Neal::Idle(float deltaTime)
{
	int changeDirection = rand() % 100;
	if (changeDirection >= 50)
	{
		int chosenNumber = rand() % 4;
		if (static_cast<int>(x) % TILE_SIZE == 0 && static_cast<int>(y) % TILE_SIZE == 0)
		{
			currDirection = static_cast<Direction>(chosenNumber);
		}
	}

	Walking(deltaTime);

	//cout << tx << ", " << ty << endl;
}

void O_Neal::Chase(float deltaTime)
{
	if (static_cast<int>(x) % TILE_SIZE == 0 && static_cast<int>(y) % TILE_SIZE == 0)
	{
		XorY = rand() % 2;
	}

#ifdef _DEBUG
	screen->Line(player1.getX() - map.getCamera(0), player1.getY(), x - map.getCamera(0), y, 0xffff00);
#endif
	float const distancePlayer1 = sqrt((player1.getX() - x) * (player1.getX() - x) + (player1.getY() - y) * (player1.getY() - y));
	float const distancePlayer2 = sqrt((player2.getX() - x) * (player2.getX() - x) + (player2.getY() - y) * (player2.getY() - y));

	float const distanceXPlayer1 = player1.getX() - x;
	float const distanceYPlayer1 = player1.getY() - y;

	float const distanceXPlayer2 = player2.getX() - x;
	float const distanceYPlayer2 = player2.getY() - y;
	//cout << distanceX << ", " << distanceY << endl;
	//cout << distancePlayer1 << ", " << distancePlayer2 << endl;

	if (distancePlayer1 < distancePlayer2 && static_cast<int>(x) % TILE_SIZE == 0 && static_cast<int>(y) % TILE_SIZE == 0)
	{
		if (distanceXPlayer1 <= 0 && XorY == 0)
		{
			currDirection = Direction::LEFT;
			//cout << "LEFT" << endl;
		}
		if (distanceXPlayer1 > 0 && XorY == 0)
		{
			currDirection = Direction::RIGHT;
			//cout << "RIGHT" << endl;
		}
		if (distanceYPlayer1 <= 0 && XorY == 1)
		{
			currDirection = Direction::UP;
			//cout << "UP" << endl;
		}
		if (distanceYPlayer1 > 0 && XorY == 1)
		{
			currDirection = Direction::DOWN;
			//cout << "DOWN" << endl;
		}
	}

	if (distancePlayer1 > distancePlayer2 && static_cast<int>(x) % TILE_SIZE == 0 && static_cast<int>(y) % TILE_SIZE == 0)
	{
		if (distanceXPlayer2 <= 0 && XorY == 0)
		{
			currDirection = Direction::LEFT;
			cout << "LEFT" << endl;
		}
		if (distanceXPlayer2 > 0 && XorY == 0)
		{
			currDirection = Direction::RIGHT;
			cout << "RIGHT" << endl;
		}
		if (distanceYPlayer2 <= 0 && XorY == 1)
		{
			currDirection = Direction::UP;
			cout << "UP" << endl;
		}
		if (distanceYPlayer2 > 0 && XorY == 1)
		{
			currDirection = Direction::DOWN;
			cout << "DOWN" << endl;
		}
	}
	Walking(deltaTime);
}

