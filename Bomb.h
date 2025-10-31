#pragma once
#include "game.h"


class Player;
class Map;
class Brick;


class Bomb
{
public:
	Bomb(Surface* screen, Player* player, Player* otherPlayer, Map* map, Audio* audio);
	~Bomb();
	//getters and setters should be class defined. I cannot get someone else's organs for example
	void Draw(Surface* surface, int camera, float deltaTime);
	bool Collision(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE);
	//bool PlayerCollision(int explosionX, int explosionY, int otherSPRITE_SIZE);
	void GetExplosionMask(int frameNumber);
	bool PlayerExplosionPixelCollision(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE, Player* thePlayer);
	bool TheCollisionPlayer(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE, Player* thePlayer);
	bool TheCollisionEnemy(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE, Enemy* theEnemy);
	bool EnemyExplosionCollision(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE, Enemy* theEnemy);


	int Min(int number1, int number2) { return (number1 < number2) ? number1 : number2; }
	int Max(int number1, int number2) { return (number1 > number2) ? number1 : number2; }


	void SetGamePtr(Game* _game) { game = _game; }
	void setEnemyPtr(Enemy** _valcom, Enemy** _oneal) { valcom = _valcom; oneal = _oneal; }
	void SetBrickPtr(Brick** _brick, int const count, int const total) {
		brick = _brick;
		brickCount = count;
		brickTotal = total;
	}

	int2 playerPos = { 0,0 };
	static constexpr int MAX_BOMBS = 2; //2
	int range = 1; //1
	bool isUsed[MAX_BOMBS] = { true, false };


	struct BombStruct
	{
		int2 position = { 0, 0 };
		bool active = false;
		bool exploded = false;
		float bombCountdown = 3.0f;
		float explosionCountdown = 1.0f;
		int frame = 0;
		int currentFrame = 0;
		float frameCountdown = 0.4f;
		float explosionFrameCountdown = 0.15f;
		int explodingLevel = 1;
	};
	bool ePressed = false;

	BombStruct bombs[MAX_BOMBS];
private:
	Surface* screen = nullptr;
	Sprite* bombSprite = nullptr;
	Sprite* explosionSprite = nullptr;

	int2 currentPlayerPos1 = { 0,0 };
	int2 currentPlayerPos2 = { 0,0 };
	int cameraX1 = 0;
	int cameraX2 = 0;
	int startPosX = 64;

	float s_frameCooldown = 0.15f;
	bool ePreviouslyPressed = false;


	//int explodingLevel = 1;

	int brickCount = 0;
	int brickTotal = 0;

	static constexpr int SPRITE_SIZE = 64;
	static constexpr int BRICK_SIZE = 64;
	static constexpr int PLAYER_SPRITE = 64;

	bool explosionPixelVisible[SPRITE_SIZE * SPRITE_SIZE] = { false };

	Player* player = nullptr;
	Player* otherPlayer = nullptr;
	Enemy** valcom = nullptr;
	Enemy** oneal = nullptr;
	Map* map = nullptr;
	Brick** brick = nullptr;
	Game* game = nullptr;
	Audio* audio = nullptr;
};

