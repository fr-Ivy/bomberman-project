#pragma once
#include "Map.h"

class Bomb;
class Brick;

class Player
{
public:
	Player(Surface* screen);
	~Player();
	void move(float deltaTime);

	void KeyDown(int key);
	void KeyUp(int key);


	void Draw();
	void Pixel();
	void SetMapPtr(Map* _map) { map = _map; }
	void SetBombPtr(Bomb* _bomb) { bomb = _bomb; }
	void SetBrickPtr(Brick** _brick, int count) {
		brick = _brick;
		brickCount = count;
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

	int brickCount = 0;
};

