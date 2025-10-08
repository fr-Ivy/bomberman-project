#include "precomp.h"
#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Brick.h"
#include "Door.h"
#include <iostream>

Player::Player(Surface* screen, float const x, float const y, int camera)
{
	playerSprite = new Sprite(new Surface("assets/player/playerSprites.png"), 19);
	this->screen = screen;
	this->x = x;
	this->y = y;
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

void Player::move(float const deltaTime)
{
	float speed = 100.0f;
	s_frame -= deltaTime;

	tx = x;
	ty = y;

	if (UP)
	{
		ty -= speed * deltaTime * 2;
		//y -= speed * deltaTime;


		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3 + 9;
			s_frame = s_frameCooldown;
		}
	}
	if (LEFT)
	{
		tx -= speed * deltaTime;
		//x -= speed * deltaTime;


		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3;
			s_frame = s_frameCooldown;
		}
	}
	if (DOWN)
	{
		ty += speed * deltaTime * 2;
		//y += speed * deltaTime;


		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3 + 3;
			s_frame = s_frameCooldown;
		}
	}
	if (RIGHT)
	{
		tx += speed * deltaTime;
		//x += speed * deltaTime;


		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3 + 6;
			s_frame = s_frameCooldown;
		}
	}

	bool brickCollision = false;
	for (int i = game->currentLevel * brickCount; i < brickCount * game->currentLevel + brickCount; i++) 
	{		
		if (brick[i] && brick[i]->checkCollision(camera, tx, ty, SPRITE_SIZE)) 
		{
			brickCollision = true;
			break;
		}
	}

	if (tx > x)
	{
		if (!map->CheckCollision(camera, tx + SPRITE_SIZE - 1, y) &&
			!map->CheckCollision(camera, tx + SPRITE_SIZE - 1, y + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			//if (!map->checkPixelCollision(pixelVisible, tx, ty, SPRITE_SIZE))
				x = tx;
		}
	}
	else if (tx < x)
	{
		if (!map->CheckCollision(camera, tx, y) &&
			!map->CheckCollision(camera, tx, y + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			//if (!map->checkPixelCollision(pixelVisible, tx, ty, SPRITE_SIZE))
				x = tx;
		}
	}

	if (ty > y)
	{
		if (!map->CheckCollision(camera, x, ty + SPRITE_SIZE - 1) &&
			!map->CheckCollision(camera, x + SPRITE_SIZE - 1, ty + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			//if (!map->checkPixelCollision(pixelVisible, tx, ty, SPRITE_SIZE))
				y = ty;
		}
	}
	else if (ty < y)
	{
		if (!map->CheckCollision(camera, x, ty) &&
			!map->CheckCollision(camera, x + SPRITE_SIZE - 1, ty) &&
			!brickCollision)
		{
			//if (!map->checkPixelCollision(pixelVisible, tx, ty, SPRITE_SIZE))
				y = ty;
		}
	}
	//bomb->getPosition(x, y);
	//cout << x << ", " << y << endl;
}

//void Player::Camera()
//{
//	map->camera(x);
//}


void Player::GoToNextLevel(float const deltaTime)
{
	doorCountdown -= deltaTime;

	if (door->collision(x, y, SPRITE_SIZE))
	{
		if (!this || !game || !door) return;

		if (doorCountdown <= 0.0f)
		{
			game->currentLevel = (game->currentLevel + 1) % 2;
			door->ChoosePosition();
			//cout << "hit" << endl;
			doorCountdown = 1.0f;
		}
	}
}

void Player::Draw(Surface* surface, int camera, int px, int TILE_SIZE)
{
	if (playerSprite)
	{
		playerSprite->Draw(surface, (x - TILE_SIZE) * px - camera, y);
		playerSprite->SetFrame(frame);
		Pixel(frame);
	}
}

int Player::Camera()
{
	return x - map->TILE_SIZE;
}


void Player::Pixel(int const frameNumber)
{
	uint32_t* pixels = playerSprite->GetBuffer();
	int frameOffset = frameNumber * SPRITE_SIZE;

	for (int ty = 0; ty < SPRITE_SIZE; ty++)
	{
		for (int tx = 0; tx < SPRITE_SIZE; tx++)
		{
			uint32_t pixel = pixels[tx + frameOffset + ty * SPRITE_SIZE * 19];
			pixelVisible[tx + ty * SPRITE_SIZE] = (pixel != 0);
			bool visible = pixelVisible[tx + ty * SPRITE_SIZE];
			if (visible)
			{
				//screen->Plot(x + tx, y + ty, 0xFF0000);
			}
		}
	}
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

