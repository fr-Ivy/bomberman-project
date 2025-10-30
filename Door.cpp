#include "precomp.h"
#include "Door.h"
#include "game.h"
#include "Brick.h"
#include "map.h"
#include <iostream>

Door::Door(Sprite* doorSprite, Surface* screen)
{
	this->doorSprite = doorSprite;
	this->screen = screen;
}

void Door::ChoosePosition()
{
	//chosenBrick = rand() % brickCount + game->currentLevel * brickCount;

	do
	{
		chosenBrick = rand() % brickCount + game->currentLevel * brickCount;
	} while (!brick[chosenBrick]);

	x = brick[chosenBrick]->getX();
	y = brick[chosenBrick]->getY();
	//cout << chosenBrick << endl;
}

bool Door::collision(int const tx, int const ty, int const otherSPRITE_SIZE)
{
	//cout << x << ", " << y << endl;
	//cout << tx << ", " << ty << endl;
	return (x < tx + otherSPRITE_SIZE && y < ty + otherSPRITE_SIZE &&
		x + SPRITE_SIZE > tx && y + SPRITE_SIZE > ty);
}

void Door::Draw(Surface* surface, int camera)
{
	cameraX = static_cast<int>(map->getCamera(camera));
	doorSprite->Draw(surface, x - cameraX, y);
}