#include "precomp.h"
#include "Brick.h"
#include "bomb.h"
#include "map.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "game.h"

Brick::Brick(Surface* screen, Bomb* bomb, Map* map)
	: bomb(bomb), map(map)
{
	this->screen = screen;
	//std::cout << "Brick constructor: " << this << std::endl;

	brickSprite = new Sprite(new Surface("assets/brickSprite.png"), 7);
}

Brick::~Brick()
{
	delete brickSprite;
}

bool Brick::CheckStartPos(int x, int y)
{
	int px = x / TILE_SIZE;
	int py = y / TILE_SIZE;

	for (int tx = 1; tx <= 4; tx++)
	{
		for (int ty = 1; ty <= 4; ty++)
		{
			if (px == tx && py == ty)
				return false;
		}
	}
	return true;
}

void Brick::choosePos()
{
	do
	{
		x = (rand() % (mapWidth / 64)) * 64;
		y = (rand() % (mapHeight / 64)) * 64;
	} while (map->CheckCollision(x, y) || !CheckStartPos(x, y));
}

bool Brick::checkCollision(int tx, int ty, int SPRITE_SIZE)
{
	cameraX = map->getCamera();
	return (x - cameraX < tx + SPRITE_SIZE && y < ty + SPRITE_SIZE &&
		x - cameraX + BRICK_SIZE > tx && y + BRICK_SIZE > ty);
}

void Brick::playAnimation(float deltaTime, bool resetFrame)
{
	if (resetFrame)
	{
		brickFrame = 0;
	}

	if (brickFrame < 7)
	{
		brickSprite->SetFrame(brickFrame);
	}

	frameCountdown -= deltaTime;

	if (frameCountdown <= 0.0f)
	{
		brickFrame = (brickFrame + 1);
		frameCountdown = 1.0f / 7.0f;
	}

	if (brickFrame >= 6 && frameCountdown <= 0.05f)
	{
		animationEnded = true;
	}
}


void Brick::Draw()
{
	if (brickSprite)
	{
		cameraX = map->getCamera();
		brickSprite->Draw(screen, x - cameraX, y);
	}
}