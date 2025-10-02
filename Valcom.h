#pragma once
#include "Enemy.h"

class Map;



class Valcom : public Enemy
{
public:
	Valcom(Surface* screen, Sprite* enemySprite, Map* map, Player* player, Game* game);

	void checkBrickCollision();
	bool checkCorners(int x1, int y1, int x2, int y2);
	void BackToTile();
	void move(float deltaTime) override;


private:
	float vX = 0.0f;
	float vY = 0.0f;
	float directionCountdown = 0.5f;
	bool BrickCollision = false;

	int lastTileX = -1;
	int lastTileY = -1;
};

