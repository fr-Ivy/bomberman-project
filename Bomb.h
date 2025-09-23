#pragma once

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
	
	void SetBrickPtr(Brick** _brick, int count) {
		brick = _brick;
		brickCount = count;
	}

private:
	Surface* screen = nullptr;
	Sprite* bombSprite = nullptr;
	Sprite* explosionSprite = nullptr;

	int2 playerPos = { 0,0 };
	int cameraX = 0.0f;
	float startPosX = 64.0f;
	int frame = 0;
	int range = 2;

	int x = 0;
	int y = 0;

	bool e_pressed = false;
	bool startCountdown = false;
	bool exploded = false;

	float bombCountdown = 3.0f;
	float explosionCountdown = 1.0f;
	float frameCountdown = 0.4f;

	int brickCount = 0;

	static constexpr float SPRITE_SIZE = 64.0f;
	static constexpr float BRICK_SIZE = 64.0f;

	Player* player = nullptr;
	Map* map = nullptr;
	Brick** brick = nullptr;
};

