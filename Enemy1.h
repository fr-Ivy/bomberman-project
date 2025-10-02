#pragma once
#include "Enemy.h"

class Map;



class Enemy1 : public Enemy
{
public:
	Enemy1(Surface* screen, Sprite* enemySprite, Map* map, Player* player, Game* game);

	void checkBrickCollision();
	void moveHorizontal(Direction currDir);
	void moveVertical(Direction currDir);
	void BackToTile();

	void move(float deltaTime) override;


private:
	int2 direction[4] = { 
		{-250,0},
		{250,0},
		{0,-250},
		{0,250}
	};
	float vX = 50.0f;
	float vY = 0.0f;
	float directionCountdown = 0.5f;
	bool BrickCollision = false;
};

