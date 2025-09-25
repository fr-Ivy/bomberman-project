#include "precomp.h"
#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Brick.h"
#include <iostream>

Player::Player(Surface* screen)
{
	playerSprite = new Sprite(new Surface("assets/player/playerSprites.png"), 19);
	this->screen = screen;
}

Player::~Player()
{
	delete playerSprite;
}

void Player::KeyUp(int key)
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
	case GLFW_KEY_E:
		E = false;
		break;
	}
}

void Player::KeyDown(int key)
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
	case GLFW_KEY_E:
		E = true;
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
			Pixel();
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
			Pixel();
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
			Pixel();
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
			Pixel();
			s_frame = s_frameCooldown;
		}
	}

	bool brickCollision = false;
	for (int i = 0; i < brickCount; i++) {
		
		if (brick[i] && brick[i]->checkCollision(tx, ty, SPRITE_SIZE)) {
			brickCollision = true;
			break;
		}
	}

	if (tx > x)
	{
		if (!map->CheckCollision(tx + SPRITE_SIZE - 1, y) &&
			!map->CheckCollision(tx + SPRITE_SIZE - 1, y + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			//if (!map->checkPixelCollision(pixelVisible, tx, ty, SPRITE_SIZE))
				x = tx;
		}
	}
	else if (tx < x)
	{
		if (!map->CheckCollision(tx, y) &&
			!map->CheckCollision(tx, y + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			//if (!map->checkPixelCollision(pixelVisible, tx, ty, SPRITE_SIZE))
				x = tx;
		}
	}

	if (ty > y)
	{
		if (!map->CheckCollision(x, ty + SPRITE_SIZE - 1) &&
			!map->CheckCollision(x + SPRITE_SIZE - 1, ty + SPRITE_SIZE - 1) &&
			!brickCollision)
		{
			//if (!map->checkPixelCollision(pixelVisible, tx, ty, SPRITE_SIZE))
				y = ty;
		}
	}
	else if (ty < y)
	{
		if (!map->CheckCollision(x, ty) &&
			!map->CheckCollision(x + SPRITE_SIZE - 1, ty) &&
			!brickCollision)
		{
			//if (!map->checkPixelCollision(pixelVisible, tx, ty, SPRITE_SIZE))
				y = ty;
		}
	}

	map->camera(x);
	//bomb->getPosition(x, y);
	//cout << x << ", " << y << endl;
}


void Player::Draw()
{
	if (playerSprite)
	{
		playerSprite->Draw(screen, x, y);
		playerSprite->SetFrame(frame);
	}
}


void Player::Pixel()
{
	uint* pixels = playerSprite->GetBuffer();

	for (int y = 0; y < SPRITE_SIZE; y++)
	{
		for (int x = 0; x < SPRITE_SIZE; x++)
		{
			uint32_t pixel = pixels[x + y * SPRITE_SIZE];
			pixelVisible[x + y * SPRITE_SIZE] = (pixel != 0);
			//cout << SPRITE_SIZE << ", " << sprite->GetBuffer() << endl;
			//cout << pixels[x + y * SPRITE_SIZE] << endl;
		}
	}
}

int2 Player::getPos()
{
	int2 tmp = { static_cast<int>(x), static_cast<int>(y) };
	return tmp;
}

bool Player::Get_E()
{
	return E;
}

