#include "precomp.h"
#include "Brick.h"
#include "bomb.h"
#include "map.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "game.h"

Brick::Brick(Surface* screen1, Surface* screen2, Bomb* bomb, Map* map)
	: bomb(bomb), map(map)
{
	this->screen1 = screen1;
	this->screen2 = screen2;
	//cout << "Brick constructor: " << this << endl;

	brickSprite = new Sprite(new Surface("assets/brickSprite.png"), 7);
}

Brick::~Brick()
{
	delete brickSprite;
}

bool Brick::CheckStartPos(int const x, int const y) const
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
	} while (map->CheckCollision(0, x, y) || !CheckStartPos(x, y));
}

bool Brick::checkCollision(int player, int tx, int ty, int SPRITE_SIZE)
{
	cameraX = 0;
	return (x - cameraX < tx + SPRITE_SIZE && y < ty + SPRITE_SIZE &&
		x - cameraX + BRICK_SIZE > tx && y + BRICK_SIZE > ty);
}

void Brick::playAnimation(float const deltaTime, bool resetFrame)
{
	if (resetFrame)
	{
		brickFrame = 0;
		resetFrame = false;
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
	cout << animationEnded << endl;
}


void Brick::Draw()
{
	if (brickSprite)
	{
		cameraX1 = map->getCamera(0);
		cameraX2 = map->getCamera(1);
		brickSprite->Draw(screen1, x - cameraX1, y);
		brickSprite->Draw(screen2, x - cameraX2, y);
	}
}