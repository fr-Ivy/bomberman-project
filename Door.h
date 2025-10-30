#pragma once
#include "game.h"

class Brick;
class Map;

class Door
{
public:
	Door(Sprite* doorSprite, Surface* screen);

	void SetBrickPtr(Brick** _brick, int count, int total) {
		brick = _brick;
		brickCount = count;
		brickTotal = total;
	}
	void SetGamePtr(Game* _game) { game = _game; }
	void SetMapPtr(Map* _map) { map = _map; }

	void ChoosePosition();
	bool collision(int tx, int ty, int otherSPRITE_SIZE);
	void Draw(Surface* surface, int camera);
private:
	Sprite* doorSprite = nullptr;
	Surface* screen = nullptr;
	Brick** brick = nullptr;
	Game* game = nullptr;
	Map* map = nullptr;

	int x = 0;
	int y = 0;
	int cameraX = 0;
	int SPRITE_SIZE = 64;

	int brickCount = 0;
	int brickTotal = 0;

	int chosenBrick = 0;
};

