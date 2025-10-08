#pragma once
#include "Enemy.h"

class Map;



class Valcom : public Enemy
{
public:
	Valcom(Surface* screen, Sprite* enemySprite, Map* map, Player* player1, Player* player2, Game* game);

	void CheckBrickCollision();
	bool CheckCorners(int x1, int y1, int x2, int y2) const;
	void BackToTile();
	void Move(float deltaTime) override;


private:
	bool BrickCollision = false;
};

