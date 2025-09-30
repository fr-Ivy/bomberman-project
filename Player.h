#pragma once
#include "game.h"
#include "map.h"

class Bomb;
class Brick;
class Door;
class Map;

class Player
{
public:
	Player(Surface* screen);
	~Player();


	void KeyDown(int key);
	void KeyUp(int key);
	void move(float deltaTime);

	void GoToNextLevel(float deltaTime);

	void Draw();
	void Pixel(int frameNumber);
	void SetMapPtr(Map* _map) { map = _map; }
	void SetBombPtr(Bomb* _bomb) { bomb = _bomb; }
	void SetGamePtr(Game* _game) { game = _game; }
	void SetDoorPtr(Door* _door) { door = _door; }
	void SetBrickPtr(Brick** _brick, int count, int total) {
		brick = _brick;
		brickCount = count;
		brickTotal = total;
	}

	int2 getPos();
	bool Get_E();
	float getX() const { return tx; }
	float getY() const { return ty; }

	static constexpr int SPRITE_SIZE = 64;

	bool pixelVisible[SPRITE_SIZE * SPRITE_SIZE] = { false };

private:
	Surface* screen = nullptr;
	Sprite* playerSprite = nullptr;

	Map* map = nullptr;
	Bomb* bomb = nullptr;
	Brick** brick = nullptr;
	Game* game = nullptr;
	Door* door = nullptr;

	int frame = 4;
	float x = 64;
	float y = 64;
	float tx = 64;
	float ty = 64;

	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool E = false;

	float s_frame = 0.2f;
	float s_frameCooldown = 0.2f;
	float doorCountdown = 0.0f;

	int brickCount = 0;
	int brickTotal = 0;
};

