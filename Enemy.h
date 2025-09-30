#pragma once
#include "game.h"

class Map;
class Player;
class Brick;

class Enemy
{
public:
	Enemy(Surface* screen, Sprite* enemySprite, Map* map, Player* player, Game* game);
	void Draw();
	void chooseRandomPos();
	virtual void move(float deltaTime);

	void SetBrickPtr(Brick** _brick, int count, int total) {
		brick = _brick;
		brickCount = count;
		brickTotal = total;
	}

	Surface* screen = nullptr;
	Sprite* enemySprite = nullptr;

	float x = 0;
	float y = 0;
	float tx = 0;
	float ty = 0;
	float screenX = 0;
	float cameraX = 0;

	int SPRITE_SIZE = 64;

	Map* map = nullptr;
	Player* player = nullptr;
	Brick** brick = nullptr;
	Game* game = nullptr;

	int brickCount = 0;
	int brickTotal = 0;

private:
	int mapHeight = 11 * 64;
	int mapWidth = 31 * 64;

};

