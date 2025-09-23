#include "precomp.h"
#include "Brick.h"
#include "bomb.h"
#include "map.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Brick::Brick(Surface* screen, Bomb* bomb, Map* map)
	: bomb(bomb), map(map)
{
	this->screen = screen;
	brickSprite = new Sprite(new Surface("assets/brick.png"), 7);
}

Brick::~Brick()
{
	delete brickSprite;
}



void Brick::choosePos()
{
	do
	{
		x = (rand() % (mapWidth / 64)) * 64;
		y = (rand() % (mapHeight / 64)) * 64;
	} while (map->CheckCollision(x, y));
}

bool Brick::checkCollision(int tx, int ty, int SPRITE_SIZE)
{
	cameraX = map->getCamera();
	return (x - cameraX < tx + SPRITE_SIZE && y < ty + SPRITE_SIZE &&
		x - cameraX + BRICK_SIZE > tx && y + BRICK_SIZE > ty);
}


void Brick::Draw()
{
	int cameraX = map->getCamera();

	if (brickSprite)
	{
		brickSprite->Draw(screen, x - cameraX, y);
	}
}