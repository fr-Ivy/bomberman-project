#include "precomp.h"
#include "Brick.h"
#include "bomb.h"
#include "map.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "game.h"
#include "Power_ups.h"

Brick::Brick(Surface* screen1, Surface* screen2, Map* map)
	:  map(map)
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

bool Brick::CheckStartPos(int const cx, int const cy) const
{
	int px = cx / TILE_SIZE;
	int py = cy / TILE_SIZE;

	for (int tx = 1; tx <= 4; tx++)
	{
		for (int ty = 1; ty <= 4; ty++)
		{
			if ((px == tx && py == ty) || (px == tx + 25 && py == ty))
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
	if (x < tx + SPRITE_SIZE)
	{
		//cout << "x hit";
	}
	if (y < ty + SPRITE_SIZE)
	{
		//cout << ", y hit";
	}

	if (x + BRICK_SIZE > tx)
	{
		//cout << "x with brick_size";
	}
	if (y + BRICK_SIZE > ty)
	{
		//cout << ", y with brick_size";
	}

	//cout << endl;

	//screen1->Line(x - cameraX1, y, tx - cameraX1, ty, 0xff00ff);
	return (x < tx + SPRITE_SIZE && y < ty + SPRITE_SIZE &&
		x + BRICK_SIZE > tx && y + BRICK_SIZE > ty);
}

void Brick::playAnimation(float const deltaTime)
{
	if (startAnimation)
	{
		if (brickFrame < 7)
		{
			brickSprite->SetFrame(brickFrame);
		}

		frameCountdown -= deltaTime;

		if (frameCountdown <= 0.0f)
		{
			brickFrame = (brickFrame + 1);
			frameCountdown = 1.5f / 7.0f;
		}

		if (brickFrame >= 7)
		{
			deleteObject = true;
		}
		cout << animationEnded << endl;
	}
}


void Brick::Draw(Surface* surface, int camera)
{
	if (brickSprite)
	{
		cameraX1 = static_cast<int>(map->getCamera(camera));
		brickSprite->Draw(surface, x - cameraX1, y);
	}
}