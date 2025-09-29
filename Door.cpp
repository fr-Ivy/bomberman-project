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
	chosenBrick = rand() % brickCount + game->currentLevel * brickCount;
	x = brick[chosenBrick]->getX();
	y = brick[chosenBrick]->getY();

	cout << chosenBrick << endl;
}

void Door::Draw()
{
	cameraX = map->getCamera();
	doorSprite->Draw(screen, x - cameraX, y);
}