#pragma once

class Player;
class Map;

class Bomb
{
public:
	Bomb() = default;
	Bomb(Sprite* sprite, Sprite* spriteExplosion, Surface* screen, Player* player, Map* map);
	~Bomb() = default;
	//getters and setters should be class defined. I cannot get someone else's organs for example
	void Draw(float deltaTime);
	
private:
	Surface* screen = nullptr;
	Sprite* spriteBomb = nullptr;
	Sprite* spriteExplosion = nullptr;

	float2 playerPos = { 0,0 };
	float cameraX = 0.0f;
	float startPosX = 64.0f;
	int frame = 0;

	bool e_pressed = false;
	bool startCountdown = false;

	float bombCountdown = 3.0f;
	float explosionCountdown = 1.0f;
	float frameCountdown = 0.4f;

	static constexpr float SPRITE_SIZE = 64.0f;

	Player* player_ = nullptr;
	Map* map_ = nullptr;
};

