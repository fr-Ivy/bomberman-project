#pragma once
#include "Power_ups.h"

class ExtraBomb : public Power_ups
{
public:
	ExtraBomb(Surface* screen, Sprite* powerUpSprite, Player* player1, Player* player2, Bomb* bomb1, Bomb* bomb2, Map* map);
	void Power() override;
private:

};

