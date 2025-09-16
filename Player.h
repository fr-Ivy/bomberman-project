#pragma once
#include "Map.h"

class Player
{
public:
	Player() = default;
	Player(Sprite* sprite, Surface* screen);
	~Player() = default;
	void move(float deltaTime);
	void Draw();
	void Pixel();
	void SetMapPtr(Map* _map) { map = _map; }

	float getX() const { return tx; }
	float getY() const { return ty; }

private:
	Surface* screen = nullptr;
	Sprite* sprite = nullptr;

	Map* map = nullptr;

	int frame = 4;
	float x = 64;
	float y = 64;
	float tx = 64;
	float ty = 64;
	static constexpr int SPRITE_SIZE = 64;
	float s_frame = 0.2f;
	float s_frameCooldown = 0.2f;
	int WidthHeight = static_cast<int>(sqrt(SPRITE_SIZE));

	bool pixelVisible[SPRITE_SIZE] = { false };
};

