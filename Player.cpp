#include "precomp.h"
#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Brick.h"
#include "Door.h"
#include "Enemy.h"
#include "Audio.h"
#include <iostream>

Player::Player(Surface* screen, float const x, float const y, int camera)
{
	playerSprite = new Sprite(new Surface("assets/player/playerSprites.png"), 19);
	this->screen = screen;
	this->x = x;
	this->y = y;
	this->startPosX = x;
	this->startPosY = y;
	this->camera = camera;
}

Player::~Player()
{
	delete playerSprite;
}

void Player::KeyUpWASD(int const key)
{
	switch (key)
	{
	case GLFW_KEY_W:
		UP = false;
		break;
	case GLFW_KEY_A:
		LEFT = false;
		break;
	case GLFW_KEY_S:
		DOWN = false;
		break;
	case GLFW_KEY_D:
		RIGHT = false;
		break;
	case GLFW_KEY_E:
		CALLBOMB = false;
		break;
	case GLFW_KEY_U:
		LEVEL_UP = false;
		break;
	default:
		break;
	}
}

void Player::KeyDownWASD(int const key)
{
	switch (key)
	{
	case GLFW_KEY_W:
		UP = true;
		break;
	case GLFW_KEY_A:
		LEFT = true;
		break;
	case GLFW_KEY_S:
		DOWN = true;
		break;
	case GLFW_KEY_D:
		RIGHT = true;
		break;
	case GLFW_KEY_E:
		CALLBOMB = true;
		break;
	case GLFW_KEY_U:
		LEVEL_UP = true;
		break;
	default:
		break;
	}
}

void Player::KeyUpARROWS(int const key)
{
	switch (key)
	{
	case GLFW_KEY_UP:
		UP = false;
		break;
	case GLFW_KEY_LEFT:
		LEFT = false;
		break;
	case GLFW_KEY_DOWN:
		DOWN = false;
		break;
	case GLFW_KEY_RIGHT:
		RIGHT = false;
		break;
	case GLFW_KEY_SLASH:
		CALLBOMB = false;
		break;
	default:
		break;
	}
}

void Player::KeyDownARROWS(int const key)
{
	switch (key)
	{
	case GLFW_KEY_UP:
		UP = true;
		break;
	case GLFW_KEY_LEFT:
		LEFT = true;
		break;
	case GLFW_KEY_DOWN:
		DOWN = true;
		break;
	case GLFW_KEY_RIGHT:
		RIGHT = true;
		break;
	case GLFW_KEY_SLASH:
		CALLBOMB = true;
		break;
	default:
		break;
	}
}

void Player::Move(float const deltaTime)
{
	float speed = 200.0f * deltaTime;
	s_frame -= deltaTime;

	tx = x;
	ty = y;

	if (UP)
	{
		ty -= speed;
		//y -= speed * deltaTime;

		audio->Play(audio->walkVerSound);

		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3 + 9;
			s_frame = s_frameCooldown;
		}
	}
	if (LEFT)
	{
		tx -= speed;
		//x -= speed * deltaTime;

		audio->Play(audio->walkHorSound);

		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3;
			s_frame = s_frameCooldown;
		}
	}
	if (DOWN)
	{
		ty += speed;
		//y += speed * deltaTime;

		audio->Play(audio->walkVerSound);

		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3 + 3;
			s_frame = s_frameCooldown;
		}
	}
	if (RIGHT)
	{
		tx += speed;
		//x += speed * deltaTime;

		audio->Play(audio->walkHorSound);

		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3 + 6;
			s_frame = s_frameCooldown;
		}
	}

	bool brickCollision = false;
	for (int i = game->currentLevel * brickCount; i < brickCount * game->currentLevel + brickCount; i++)
	{
		if (brick[i] && brick[i]->checkCollision(static_cast<int>(tx), static_cast<int>(ty), SPRITE_SIZE))
		{
			brickCollision = true;
			break;
		}
	}

	if (tx > x)
	{
		if (!map->CheckCollision(static_cast<int>(tx) + SPRITE_SIZE - 1, static_cast<int>(y)) &&
			!map->CheckCollision(static_cast<int>(tx) + SPRITE_SIZE - 1, static_cast<int>(y) + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			if (!map->checkPixelCollision(this, static_cast<int>(tx), static_cast<int>(ty), SPRITE_SIZE))
			{
				x = tx;
			}
		}
	}
	else if (tx < x)
	{
		if (!map->CheckCollision(static_cast<int>(tx), static_cast<int>(y)) &&
			!map->CheckCollision(static_cast<int>(tx), static_cast<int>(y) + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			if (!map->checkPixelCollision(this, static_cast<int>(tx), static_cast<int>(ty), SPRITE_SIZE))
			{
				x = tx;
			}
		}
	}

	if (ty > y)
	{
		if (!map->CheckCollision(static_cast<int>(x), static_cast<int>(ty) + SPRITE_SIZE - 1) &&
			!map->CheckCollision(static_cast<int>(x) + SPRITE_SIZE - 1, static_cast<int>(ty) + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			if (!map->checkPixelCollision(this, static_cast<int>(tx), static_cast<int>(ty), SPRITE_SIZE))
			{
				y = ty;
			}
		}
	}
	else if (ty < y)
	{
		if (!map->CheckCollision(static_cast<int>(x), static_cast<int>(ty)) &&
			!map->CheckCollision(static_cast<int>(x) + SPRITE_SIZE - 1, static_cast<int>(ty)) &&
			!brickCollision)
		{
			if (!map->checkPixelCollision(this, static_cast<int>(tx), static_cast<int>(ty), SPRITE_SIZE))
			{
				y = ty;
			}
		}
	}
	//bomb->getPosition(x, y);
	//cout << x << ", " << y << endl;


	for (int i = 0; i < 9; i++)
	{
		if (valcom[i])
		{
			if (CheckAABBCollision(valcom[i]->x, valcom[i]->y, valcom[i]->SPRITE_SIZE))
			{
				Pixel(frame);
				cout << "AABB" << endl;
				if (PlayerPixelCollision(valcom[i], static_cast<int>(valcom[i]->x), static_cast<int>(valcom[i]->y), valcom[i]->SPRITE_SIZE))
				{
					cout << "PIXEL PERFECT" << endl;

					if (valcom[i]->inLevel)
					{
						startDyingAnimation = true;
						valcom[i]->ChooseRandomPos();
					}
				}
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (oneal[i])
		{
			if (CheckAABBCollision(oneal[i]->x, oneal[i]->y, oneal[i]->SPRITE_SIZE))
			{
				Pixel(frame);
				cout << "AABB" << endl;
				if (PlayerPixelCollision(oneal[i], static_cast<int>(oneal[i]->x), static_cast<int>(oneal[i]->y), oneal[i]->SPRITE_SIZE))
				{
					cout << "PIXEL PERFECT" << endl;
					if (oneal[i]->inLevel)
					{
						startDyingAnimation = true;
						oneal[i]->ChooseRandomPos();
					}
				}
			}
		}
	}
}

//void Player::Camera()
//{
//	map->camera(x);
//}


bool Player::GoToNextLevel()
{
	if (door->collision(static_cast<int>(x), static_cast<int>(y), SPRITE_SIZE))
	{
		//if (!this || !game || !door) return false;

		game->currentLevel = (game->currentLevel + 1) % 2;
		door->ChoosePosition();
		//cout << "hit" << endl;
		doorCountdown = 1.0f;
		for (int i = 0; i < 9; i++)
		{
			if (valcom[i])
			{
				valcom[i]->ChooseRandomPos();
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (oneal[i])
			{
				oneal[i]->ChooseRandomPos();
			}
		}

		return true;
	}
	return false;
}

void Player::Draw(Surface* surface, float const theCamera)
{
	if (playerSprite)
	{
		playerSprite->Draw(surface, static_cast<int>(x - theCamera), static_cast<int>(y));
		if (dying)
		{
			playerSprite->SetFrame(dyingFrame + 12);
		}
		else
		{
			playerSprite->SetFrame(frame);
		}
		//Pixel(frame);
	}
}

bool Player::CheckAABBCollision(float const otherX, float const otherY, int const otherSPRITE_SIZE) const
{
#ifdef _DEBUG
	screen->Box(static_cast<int>(otherX), static_cast<int>(otherY), 
		static_cast<int>(otherX) + otherSPRITE_SIZE, static_cast<int>(otherY) + otherSPRITE_SIZE, 0xfc0303);
	screen->Box(static_cast<int>(tx), static_cast<int>(ty), 
		static_cast<int>(tx) + SPRITE_SIZE, static_cast<int>(ty) + SPRITE_SIZE, 0xfc0303);
#endif
	return (otherX < tx + SPRITE_SIZE && otherY < ty + SPRITE_SIZE &&
		otherX + static_cast<float>(otherSPRITE_SIZE) > tx && otherY + static_cast<float>(otherSPRITE_SIZE) > ty);
}


void Player::Pixel(int const frameNumber)
{
	const uint32_t* pixels = playerSprite->GetBuffer();
	int frameOffset = frameNumber * SPRITE_SIZE;

	for (int py = 0; py < SPRITE_SIZE; py++)
	{
		for (int px = 0; px < SPRITE_SIZE; px++)
		{
			const uint32_t pixel = pixels[px + frameOffset + py * SPRITE_SIZE * 19];
			pixelVisible[px + py * SPRITE_SIZE] = (pixel != 0);
			bool visible = pixelVisible[px + py * SPRITE_SIZE];
			if (visible)
			{
				//game->screen->Plot(x + tx, y + ty, 0xFF0000);
			}
		}
	}
}

void Player::DyingAnimation(float deltaTime)
{
	//cout << startDyingAnimation << endl;
	if (startDyingAnimation)
	{
		if (dyingFrame < 7)
		{
			//playerSprite->SetFrame(dyingFrame + 12);
			dying = true;
		}

		dyingFrameCountdown -= deltaTime;

		if (dyingFrameCountdown <= 0.0f)
		{
			dyingFrame = (dyingFrame + 1) % 8;
			dyingFrameCountdown = 3.0f / 7.0f;
		}

		if (dyingFrame >= 7)
		{
			startDyingAnimation = false;
			ResetPosition();
			dyingFrame = 0;
			dying = false;
			game->showGameOver = true;
			game->showGame = false;
		}
	}
}


void Player::ResetPosition()
{
	x = startPosX;
	y = startPosY;
}

int2 Player::getPos() const
{
	int2 tmp = { static_cast<int>(x), static_cast<int>(y) };
	return tmp;
}

bool Player::Get_E() const
{
	return CALLBOMB;
}

bool Player::PlayerPixelCollision(Enemy* enemy, int const px, int const py, int const otherSPRITE_SIZE) const
{
	int playerLeft = static_cast<int>(x);
	int const playerRight = static_cast<int>(x) + otherSPRITE_SIZE;
	int playerTop = static_cast<int>(y);
	int const playerBottom = static_cast<int>(y) + otherSPRITE_SIZE;

	int enemyLeft = px;
	int const enemyRight = px + SPRITE_SIZE;
	int enemyTop = py;
	int const enemyBottom = py + SPRITE_SIZE;

	int const left = max(playerLeft, enemyLeft);
	int const right = min(playerRight, enemyRight);
	int const top = max(playerTop, enemyTop);
	int const bottom = min(playerBottom, enemyBottom);
	int const columns = right - left;
	int const rows = bottom - top;
	//cout << "columns: " << columns << ", rows: " << rows << endl;

	playerLeft = left - playerLeft;
	playerTop = top - playerTop;
	enemyLeft = left - enemyLeft;
	enemyTop = top - enemyTop;

	bool hit = false;

	for (int py1 = 0; py1 < rows; py1++)
	{
		for (int px1 = 0; px1 < columns; px1++)
		{
			if (pixelVisible[(playerLeft + px1) + (playerTop + py1) * otherSPRITE_SIZE] &&
				enemy->enemyPixelVisible[(enemyLeft + px1) + (enemyTop + py1) * SPRITE_SIZE])
			{
				//cout << "hit" << endl;
				game->screen1->Plot(left + px1 - static_cast<int>(map->getCamera(camera)), top + py1, 0x002880);
				game->screen2->Plot(left + px1 - static_cast<int>(map->getCamera(camera)), top + py1, 0x002880);
				hit = true;
			}
		}
	}
	return hit;

	//recources: https://croakingkero.com/tutorials/pixel_collision_detection/
}