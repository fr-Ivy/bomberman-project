#pragma once
#include "Enemy.h"

class Map;

class Enemy1 : public Enemy
{
public:
	Enemy1(Surface* screen, Sprite* enemySprite, Map* map, Player* player, Game* game);


	void move(float deltaTime) override;


private:
	float vX = 250.0f;
	float vY = 0.0f;
	float directionCountdown = 0.5f;
};

