#pragma once
#include "game.h"
#include "map.h"

class Bomb;
class Brick;
class Door;
class Map;
class Enemy;
class Audio;

class Player
{
public:
	Player(Surface* screen, float x, float y, int camera);
	~Player();


	void KeyDownWASD(int key);
	void KeyUpWASD(int key);
	void KeyDownARROWS(int key);
	void KeyUpARROWS(int key);
	void Move(float deltaTime);
	bool GoToNextLevel();

	void Draw(Surface* surface, float theCamera);
	bool CheckAABBCollision(float otherX, float otherY, int otherSPRITE_SIZE) const;
	void Pixel(int frameNumber);
	bool PlayerPixelCollision(Enemy* enemy, int px, int py, int otherSPRITE_SIZE);
	void DyingAnimation(float deltaTime);
	void ResetPosition();
	void SetMapPtr(Map* _map) { map = _map; }
	void SetBombPtr(Bomb* _bomb) { bomb = _bomb; }
	void SetGamePtr(Game* _game) { game = _game; }
	void SetDoorPtr(Door* _door) { door = _door; }
	void SetAudioPtr(Audio* _audio) { audio = _audio; }
	void setEnemyPtr(Enemy** _valcom, Enemy** _oneal) { valcom = _valcom; oneal = _oneal; }
	void SetBrickPtr(Brick** _brick, int count, int total) {
		brick = _brick;
		brickCount = count;
		brickTotal = total;
	}

	int2 getPos() const;
	bool Get_E() const;
	float getX() const { return x; }
	float getY() const { return y; }

	int Min(int number1, int number2) { return (number1 < number2) ? number1 : number2; }
	int Max(int number1, int number2) { return (number1 > number2) ? number1 : number2; }

	static constexpr int SPRITE_SIZE = 64;

	bool pixelVisible[SPRITE_SIZE * SPRITE_SIZE] = { false };
	int frame = 4;
	int dyingFrame = 0;
	bool startDyingAnimation = false;
	bool dying = false;
	bool LEVEL_UP = false;

private:
	Surface* screen = nullptr;
	Sprite* playerSprite = nullptr;

	Map* map = nullptr;
	Bomb* bomb = nullptr;
	Brick** brick = nullptr;
	Game* game = nullptr;
	Door* door = nullptr;
	Enemy** valcom = nullptr;
	Enemy** oneal = nullptr;
	Audio* audio = nullptr;

	float startPosX = 0.0f;
	float startPosY = 0.0f;

	float x = 0.0f;
	float y = 0.0f;
	float tx = 0.0f;
	float ty = 0.0f;
	int camera = 0;

	bool UP = false;
	bool LEFT = false;
	bool DOWN = false;
	bool RIGHT = false;
	bool CALLBOMB = false;


	float s_frame = 0.2f;
	float s_frameCooldown = 0.2f;
	float doorCountdown = 0.0f;
	float dyingFrameCountdown = 0.0f;

	int brickCount = 0;
	int brickTotal = 0;
};

