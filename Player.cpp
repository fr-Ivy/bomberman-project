#include "precomp.h"
#include "Player.h"
#include "game.h"
#include "Map.h"
#include <iostream>

Player::Player(Sprite* sprite, Surface* screen)
{
	this->sprite = sprite;
	this->screen = screen;
}

bool W = false;
bool A = false;
bool S = false;
bool D = false;

void Game::KeyUp(int key)
{
	switch (key)
	{
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		W = false;
		break;
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		A = false;
		break;
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		S = false;
		break;
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		D = false;
		break;
	}
}

void Game::KeyDown(int key)
{
	switch (key)
	{
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		W = true;
		break;
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		A = true;
		break;
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		S = true;
		break;
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		D = true;
		break;
	}
}

void Player::move(float deltaTime)
{
	deltaTime /= 1000.0f;
	float speed = 100.0f;
	s_frame -= deltaTime;

	tx = x;
	ty = y;

	if (W)
	{
		ty -= speed * deltaTime * 2;
		//y -= speed * deltaTime;


		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3 + 9;
			s_frame = s_frameCooldown;
		}
	}
	if (A)
	{
		tx -= speed * deltaTime;
		//x -= speed * deltaTime;


		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3;
			s_frame = s_frameCooldown;
		}
	}
	if (S)
	{
		ty += speed * deltaTime * 2;
		//y += speed * deltaTime;


		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3 + 3;
			s_frame = s_frameCooldown;
		}
	}
	if (D)
	{
		tx += speed * deltaTime;
		//x += speed * deltaTime;


		if (s_frame <= 0.0f)
		{
			frame = (frame + 1) % 3 + 6;
			s_frame = s_frameCooldown;
		}
	}

	if (tx > x)
	{
		if (!map->CheckCollision(tx + SPRITE_SIZE - 1, y) &&
			!map->CheckCollision(tx + SPRITE_SIZE - 1, y + SPRITE_SIZE - 1))
		{
			for (int i = 0; i < SPRITE_SIZE; i++)
			{
				if (pixelVisible[i])
				{
					if (!map->checkPixelCollision(i, SPRITE_SIZE, tx, y) ||
						!map->checkPixelCollision(i, SPRITE_SIZE, tx, y + SPRITE_SIZE - 1))
					{
						x = tx;
					}
				}
			}
		}
	}

	else if (tx < x)
	{
		if (!map->CheckCollision(tx, y) &&
			!map->CheckCollision(tx, y + SPRITE_SIZE - 1))
		{
			for (int i = 0; i < SPRITE_SIZE; i++)
			{
				if (pixelVisible[i])
				{
					if (!map->checkPixelCollision(i, SPRITE_SIZE, tx, y) ||
						!map->checkPixelCollision(i, SPRITE_SIZE, tx, y + SPRITE_SIZE - 1))
					{
						x = tx;
					}
				}
			}
		}
	}

	if (ty > y)
	{
		if (!map->CheckCollision(x, ty + SPRITE_SIZE - 1) &&
			!map->CheckCollision(x + SPRITE_SIZE - 1, ty + SPRITE_SIZE - 1))
		{
			for (int i = 0; i < SPRITE_SIZE; i++)
			{
				if (pixelVisible[i])
				{
					if (!map->checkPixelCollision(i, SPRITE_SIZE, x, ty + SPRITE_SIZE - 1) ||
						!map->checkPixelCollision(i, SPRITE_SIZE, x + SPRITE_SIZE - 1, ty + SPRITE_SIZE - 1))
					{
						y = ty;
					}
				}
			}
		}
	}
	else if (ty < y)
	{
		if (!map->CheckCollision(x, ty) &&
			!map->CheckCollision(x + SPRITE_SIZE - 1, ty))
		{
			for (int i = 0; i < SPRITE_SIZE; i++)
			{
				if (pixelVisible[i])
				{
					if (!map->checkPixelCollision(i, SPRITE_SIZE, x, ty) ||
						!map->checkPixelCollision(i, SPRITE_SIZE, x + SPRITE_SIZE - 1, ty))
					{
						y = ty;
					}
				}
			}
		}
	}

	map->camera(x);
	cout << x << ", " << y << endl;
}


void Player::Draw()
{
	if (sprite)
	{
		sprite->Draw(screen, x, y);
		sprite->SetFrame(frame);
	}
}


void Player::Pixel()
{
	uint* pixels = sprite->GetBuffer();

	for (int i = 0; i < SPRITE_SIZE; i++)
	{
		uint32_t pixel = pixels[i];

		if (pixel != 0)
		{
			pixelVisible[i] = true;
		}
		else
		{
			pixelVisible[i] = false;
		}
		//cout << i << pixelVisible[i] << endl;
	}
}