#include "precomp.h"
#include "ExtraBomb.h"
#include "Bomb.h"

ExtraBomb::ExtraBomb(Surface* screen, Sprite* powerUpSprite, Player* player1, Player* player2, Bomb* bomb1, Bomb* bomb2, Map* map)
	: Power_ups(screen, powerUpSprite, player1, player2, bomb1, bomb2, map)
{
}

void ExtraBomb::Power()
{
	if (Collision1())
	{
		bomb1->isUsed[1] = true;
		deleteObject = true;
	}
	if (Collision2())
	{
		bomb2->isUsed[1] = true;
		deleteObject = true;
	}
}

