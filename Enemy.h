#pragma once
#include "game.h"

class Map;
class Player;
class Brick;
class Bomb;

enum class Direction
{
	 LEFT, RIGHT, UP, DOWN, NONE,
};

class Enemy
{
public:
	Enemy(Surface* screen, Sprite* enemySprite, Map& map, Player& player1, Player& player2, Game* game, int points);
	void CheckBrickCollision(int px, int py);
	void Draw(Surface* surface, int camera);
	bool CheckStartPos(int cx, int cy) const;
	void ChooseRandomPos();
	bool CheckCorners(int x1, int y1, int x2, int y2) const;
	void BackToTile();
	virtual void Move(float deltaTime);
	void WalkingAnitmation(float deltaTime);
	void DyingAnimation(float deltaTime);
	void Pixel(int frameNumber);
	bool MarkForDeletion() const { return deleteObject; }
	bool BombCollision() const;

	void SetBrickPtr(Brick** _brick, int count, int total) {
		brick = _brick;
		brickCount = count;
		brickTotal = total;
	}

	void SetBombPtr(Bomb* _bomb1, Bomb* _bomb2) { bomb1 = _bomb1; bomb2 = _bomb2; }

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
	float speed = 100.0f;
	bool brickCollision = false;
	bool deleteObject = false;

	static constexpr int SPRITE_SIZE = 64;
	static constexpr int TILE_SIZE = 64;

	Map& map;
	Player& player1;
	Player& player2;
	Brick** brick = nullptr;
	Game* game = nullptr;
	Bomb* bomb1 = nullptr;
	Bomb* bomb2 = nullptr;

	int brickCount = 0;
	int brickTotal = 0;
	Direction currDirection = Direction::NONE;

	bool enemyPixelVisible[SPRITE_SIZE * SPRITE_SIZE] = { false };

	int frame = 0;
	bool startDyingAnimation = false;
	bool dying = false;
	bool inLevel = false;

private:
	int mapHeight = 11 * 64;
	int mapWidth = 31 * 64;

	float walkingFrameCountdown = 0.0f;
	int dyingFrame = 0;
	float dyingFrameCountdown = 0.0f;
	int points = 0;
};

