#pragma once
#include "game.h"
class Player;
class Bomb;
class Map;
class Brick;

class Power_ups
{
public:
	Power_ups(Surface* screen, Sprite* powerUpSprite, Player* player1, Player* player2, Bomb* bomb1, Bomb* bomb2, Map* map);
	~Power_ups();
	void ChoosePos(int level);
	void Draw(Surface* surface, int camera);
	bool Collision1();
	bool Collision2();
	virtual void Power();
	bool MarkForDeletion() const { return deleteObject; }

	void SetBrickPtr(Brick** _brick, int count, int total) {
		brick = _brick;
		brickCount = count;
		brickTotal = total;
	}

	Player* player1 = nullptr;
	Player* player2 = nullptr;
	Bomb* bomb1 = nullptr;
	Bomb* bomb2 = nullptr;
	Map* map = nullptr;
	Brick** brick = nullptr;

	int SPRITE_SIZE = 64;
	bool deleteObject = false;
private:
	float x = 150.0f;
	float y = 64.0f;
	Surface* screen = nullptr;
	Sprite* powerUpSprite = nullptr;
	int brickCount = 0;
	int brickTotal = 0;

	int chosenBrick = 0;
};

