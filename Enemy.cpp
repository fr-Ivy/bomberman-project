#include "precomp.h"
#include "Enemy.h"
#include "map.h"
#include "Brick.h"
#include <iostream>

Enemy::Enemy(Surface* screen, Sprite* enemySprite, Map* map, Player* player, Game* game)
	: map(map), player(player), game(game)
{
	this->screen = screen;
	this->enemySprite = enemySprite;
}

void Enemy::Draw()
{
	cameraX = map->getCamera();
	screenX = x - cameraX;
	enemySprite->Draw(screen, screenX, y);
}

void Enemy::chooseRandomPos()
{
	do
	{
		x = (rand() % (mapWidth / 64)) * 64;
		y = (rand() % (mapHeight / 64)) * 64;
	} while (map->CheckCollision(x, y));
	cout << x << ", " << y << endl;
}

void Enemy::move(float deltaTime)
{
	cout << "should never be reached" << endl;
}
