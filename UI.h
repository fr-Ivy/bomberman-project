#pragma once
class UI
{
public:
	UI(Surface* surface, int x, int y);
	void Draw(Surface* screen);
private:
	Surface* surface = nullptr;
	int x = 0;
	int y = 0;
};

