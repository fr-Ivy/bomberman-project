#pragma once

class Bomb;
class Map;

class Brick
{
public:
	Brick(Surface* screen, Bomb* bomb, Map* map);
	~Brick();
	bool CheckStartPos(int x, int y);
	void choosePos();
	bool checkCollision(int tx, int ty, int SPRITE_SIZE);
	void playAnimation(float deltaTime, bool resetFrame);
	void Draw();

	int getX() const { return x; }
	int getY() const { return y; }
	bool animationEnded = false;

private:
	Surface* screen = nullptr;
	Sprite* brickSprite = nullptr;

	int mapHeight = 11 * 64;
	int mapWidth = 31 * 64;
	int TILE_SIZE = 64;

	int x = 0;
	int y = 0;
	int cameraX = 0;

	float animationDuration = 1.4f;
	float frameCountdown = 1.0f / 7.0f;


	int BRICK_SIZE = 64;
	int brickFrame = 0;

	bool collision = false;

	Bomb* bomb = nullptr;
	Map* map = nullptr;
};

