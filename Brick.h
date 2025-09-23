#pragma once

class Bomb;
class Map;

class Brick
{
public:
	Brick(Surface* screen, Bomb* bomb, Map* map);
	~Brick();
	void choosePos();
	bool checkCollision(int tx, int ty, int SPRITE_SIZE);
	void Draw();

	int getX() const { return x; }
	int getY() const { return y; }


private:
	Surface* screen = nullptr;
	Sprite* brickSprite = nullptr;

	int mapHeight = 11 * 64;
	int mapWidth = 31 * 64;

	int x = 0;
	int y = 0;
	int cameraX = 0;

	int BRICK_SIZE = 64;

	bool collision = false;

	Bomb* bomb = nullptr;
	Map* map = nullptr;
};

