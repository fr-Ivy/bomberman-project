#include "precomp.h"
#include "ExtraFlameRange.h"

#include "Bomb.h"


ExtraFlameRange::ExtraFlameRange(Surface* screen, Sprite* powerUpSprite, Player* player1, Player* player2, Bomb* bomb1, Bomb* bomb2, Map* map)
	: Power_ups(screen, powerUpSprite, player1, player2, bomb1, bomb2, map)
{
}

void ExtraFlameRange::Power()
{
	if (Collision1())
	{
		bomb1->range++;
		deleteObject = true;
	}
	if (Collision2())
	{
		bomb2->range++;
		deleteObject = true;
	}
}
