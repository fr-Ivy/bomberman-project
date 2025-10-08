#include "precomp.h"
#include "Enemy.h"
#include "map.h"
#include "Brick.h"
#include <iostream>

Enemy::Enemy(Surface* screen, Sprite* enemySprite, Map* map, Player* player1, Player* player2, Game* game)
	: map(map), player1(player1), game(game), player2(player2)
{
	this->screen = screen;
	this->enemySprite = enemySprite;
}

void Enemy::Draw(Surface* surface, int camera)
{
	cameraX1 = map->getCamera(camera); //
	screenX = x - cameraX1;
	enemySprite->Draw(surface, screenX, y);
}

void Enemy::ChooseRandomPos()
{
	do
	{
		x = static_cast<float>(rand() % (mapWidth / 64) * 64);
		y = static_cast<float>(rand() % (mapHeight / 64) * 64);
	} while (map->CheckCollision(0, x, y));
	//cout << x << ", " << y << endl;
}

void Enemy::Move(float const deltaTime)
{
	cout << "should never be reached" << endl;
}
