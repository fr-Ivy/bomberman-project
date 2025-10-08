#pragma once
#include "game.h"

class Map;
class Player;
class Brick;

enum class Direction
{
	 LEFT, RIGHT, UP, DOWN, NONE,
};

class Enemy
{
public:
	Enemy(Surface* screen, Sprite* enemySprite, Map* map, Player* player1, Player* player2, Game* game);
	void Draw(Surface* surface, int camera);
	void ChooseRandomPos();
	virtual void Move(float deltaTime);

	void SetBrickPtr(Brick** _brick, int count, int total) {
		brick = _brick;
		brickCount = count;
		brickTotal = total;
	}

	Surface* screen = nullptr;
	Sprite* enemySprite = nullptr;

	float x = 0.0f;
	float y = 0.0f;
	float tx = 0.0f;
	float ty = 0.0f;
	float vX = 0.0f;
	float vY = 0.0f;
	float screenX = 0;
	float cameraX1 = 0;
	float cameraX2 = 0;

	int SPRITE_SIZE = 64;
	int TILE_SIZE = 64;

	Map* map = nullptr;
	Player* player1 = nullptr;
	Player* player2 = nullptr;
	Brick** brick = nullptr;
	Game* game = nullptr;

	int brickCount = 0;
	int brickTotal = 0;
	Direction currDirection = Direction::NONE;

private:
	int mapHeight = 11 * 64;
	int mapWidth = 31 * 64;

};

