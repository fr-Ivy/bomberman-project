#pragma once
#include "game.h"
class Arrow
{
public:
	Arrow(Sprite* sprite);
	void keyDown(int key);
	void move();
	void Draw(Surface* screen) const;
	void SetGamePtr(Game* _game) { game = _game; }
private:
	Game* game = nullptr;
	Sprite* arrow = nullptr;
	int startPosX = 450;
	int secondStartPosX = 650;
	int x = startPosX;
	int y = 400;

};

