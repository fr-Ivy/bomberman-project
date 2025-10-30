#pragma once
#include "Enemy.h"

enum class status
{
	IDLE, CHASE
};


class O_Neal : public Enemy
{
public:
	O_Neal(Surface* screen, Sprite* enemySprite, Map& map, Player& player1, Player& player2, Game* game, int points);
	void Move(float deltaTime) override;
	void Idle(float deltaTime);
	void Chase(float deltaTime);
	void Walking(float deltaTime);

private:
	status currStatus = status::CHASE;
	int XorY = 0;
};