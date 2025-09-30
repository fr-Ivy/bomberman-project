// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#pragma once

class Player; //Forward declaration
class Map;
class Bomb;
class Brick;
class Door;
class Enemy;

namespace Tmpl8
{

class Game : public TheApp
{
public:
	// game flow methods
	void Init();
	void Tick( float deltaTime );
	void Shutdown() { /* implement if you want to do something on exit */ }
	// input handling
	void MouseUp( int ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { mousePos.x = x, mousePos.y = y; }
	void MouseWheel( float ) { /* implement if you want to handle the mouse wheel */ }
	void KeyUp(int key);
	void KeyDown(int key);

	void deleteBrick(int index);
	void Level0();
	void Level1();
	// data members
	int2 mousePos;

	Map* map = nullptr;
	Player* player = nullptr;
	Bomb* bomb = nullptr;
	Door* door = nullptr;
	Enemy* enemy1 = nullptr;


	static constexpr int amountBricks = 20; //80
	static constexpr int levels = 2;
	int currentLevel = 0;
	Brick* bricks[amountBricks * levels];

	Sprite* doorSprite = nullptr;
	Sprite* enemySprite1 = nullptr;
};

} // namespace Tmpl8