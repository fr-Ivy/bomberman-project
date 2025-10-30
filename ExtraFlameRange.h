#pragma once
#include "Power_ups.h"

class ExtraFlameRange : public Power_ups
{
public:
	ExtraFlameRange(Surface* screen, Sprite* powerUpSprite, Player* player1, Player* player2, Bomb* bomb1, Bomb* bomb2, Map* map);
	void Power() override;
private:

};

