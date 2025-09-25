#pragma once
#include "game.h"


class Player;
class Map;
class Brick;


class Bomb
{
public:
	Bomb(Surface* screen, Player* player, Map* map);
	~Bomb();
	//getters and setters should be class defined. I cannot get someone else's organs for example
	void Draw(float deltaTime);
	bool Collision(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE);
	void getExplosionMask(int frameNumber);
	bool PlayerExplosionCollision(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE);

	void SetGamePtr(Game* _game) { game = _game; }

	void SetBrickPtr(Brick** _brick, int count) {
		brick = _brick;
		brickCount = count;
	}

private:
	Surface* screen = nullptr;
	Sprite* bombSprite = nullptr;
	Sprite* explosionSprite = nullptr;

	int2 playerPos = { 0,0 };
	int2 currentPlayerPos = { 0,0 };
	int cameraX = 0.0f;
	float startPosX = 64.0f;
	int frame = 0;
	int range = 2;

	int x = 0;
	int y = 0;

	bool e_pressed = false;
	bool startCountdown = false;
	bool exploded = false;
	bool playerCollision = false;
	bool resetBrickFrame = false;

	int currentFrame = 0;

	float bombCountdown = 3.0f;
	float explosionCountdown = 10.0f;
	float frameCountdown = 0.4f;
	float explosionFrameCountdown = 0.15f;
	float s_frameCooldown = 0.15f;

	int explodingLevel = 1;

	int brickCount = 0;

	static constexpr int SPRITE_SIZE = 64;
	static constexpr float BRICK_SIZE = 64.0f;
	static constexpr float PLAYER_SPRITE = 64.0f;

	bool ExplosionPixelVisible[SPRITE_SIZE * SPRITE_SIZE] = { false };

	Player* player = nullptr;
	Map* map = nullptr;
	Brick** brick = nullptr;
	Game* game = nullptr;
};

