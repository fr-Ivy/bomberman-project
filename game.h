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
class Power_ups;
class Audio;
class UI;
class Arrow;

namespace Tmpl8
{

class Game : public TheApp
{
public:
	// game flow methods
	~Game();
	void Init();
	void Tick( float deltaTime );
	void Shutdown() { /* implement if you want to do something on exit */ }
	// input handling
	void MouseUp( int ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(int x, int y) { mousePos.x = x, mousePos.y = y; }
	void MouseWheel( float ) { /* implement if you want to handle the mouse wheel */ }
	void KeyUp(int key);
	void KeyDown(int key);

	void DeleteBrick(int index);
	void Level0(float deltaTime);
	void Level1(float deltaTime);
	bool AllFalse(int start, int end1, int start2, int end2);
	// data members
	int2 mousePos;

	static constexpr int amountValcoms = 9;
	static constexpr int amountONeals = 3;

	Map* map = nullptr;
	Player* player[2] = { nullptr };
	Bomb* bomb[2] = { nullptr };
	Door* door = nullptr;
	Enemy* valcom[amountValcoms] = { nullptr };
	Enemy* ONeal[amountONeals] = { nullptr };
	Power_ups* extraFlameRange = nullptr;
	Power_ups* extraBomb = nullptr;
	Audio* audio = nullptr;
	UI* menuUI = nullptr;
	UI* gameOverUI = nullptr;
	UI* gameModeUI = nullptr;
	UI* controlsUI = nullptr;
	Arrow* arrow = nullptr;

	int currentLevel = 0;
	int gameMode = 1; //1 = single-player, 2 = two-player
	int TILE_SIZE = 64;

	static constexpr int amountBricks = 80; //80
	static constexpr int levels = 2;
	Brick* bricks[amountBricks * levels];

	Sprite* doorSprite = nullptr;
	Sprite* valcomSprite = nullptr;
	Sprite* ONealSprite = nullptr;
	Sprite* extraFlameRangeSprite = nullptr;
	Sprite* extraBombSprite = nullptr;

	Surface* screen2 = nullptr;
	Surface* screen1 = nullptr;
	Surface* menuScreen = nullptr;
	Surface* gameOverScreen = nullptr;
	Surface* gameModeScreen = nullptr;
	Surface* controlsScreen = nullptr;
	Sprite* menuArrow = nullptr;

	bool showGame = false;
	bool showMenu = true;
	bool showGameOver = false;
	bool showControls = false;
	bool showGameMode = false;

	bool pressedPlay = false;

	int score = 0;
};

} // namespace Tmpl8