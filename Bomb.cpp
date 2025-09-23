#include "precomp.h"
#include "Bomb.h"
#include "Player.h"
#include "Brick.h"
#include <iostream>

Bomb::Bomb(Surface* screen, Player* player, Map* map) 
	: player(player), map(map)
{
	this->screen = screen;

	bombSprite = new Sprite(new Surface("assets/bomb.png"), 3);
	explosionSprite = new Sprite(new Surface("assets/explosionSprite.png"), 36);
}

Bomb::~Bomb()
{
	delete bombSprite;
	delete explosionSprite;
}


void Bomb::Draw(float deltaTime)
{
	deltaTime /= 1000.0f;
	e_pressed = player->Get_E();
	cameraX = map->getCamera();

	//if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
	//{
	//	e_pressed = true;
	//}

	if (e_pressed && !startCountdown)
	{
		startCountdown = true;
		bombCountdown = 3.0f;
		explosionCountdown = 1.0f;
		playerPos = player->getPos();
		cameraX = playerPos.x;
		playerPos.x = (playerPos.x + cameraX) / 64 * 64 - startPosX;
		playerPos.y = playerPos.y / 64 * 64;
	}

	if (bombSprite && startCountdown)
	{
		if (bombCountdown >= 0.0f)
		{
			bombCountdown -= deltaTime;

			bombSprite->Draw(screen, playerPos.x - cameraX, playerPos.y);
			//cout << "cameraX: " << cameraX << endl;
			bombSprite->SetFrame(frame);

			frameCountdown -= deltaTime;

			if (frameCountdown <= 0.0f)
			{
				frame = (frame + 1) % 3;
				frameCountdown = 0.4f;
			}

			//cout << "bombCountdown: " << bombCountdown << endl;
		}
		else if (explosionSprite && explosionCountdown >= 0.0f)
		{
			explosionCountdown -= deltaTime;


			explosionSprite->SetFrame(0);
			explosionSprite->Draw(screen, playerPos.x - cameraX, playerPos.y);

			int2 directions[4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

			for (int j = 0; j < 4; j++) //drawing to every direction
			{
				float position = 64.0f;
				for (int i = 0; i < range; i++) // change range
				{
					int positionX = position * directions[j].x;
					int positionY = position * directions[j].y;

					int explosionX = positionX + playerPos.x;
					int explosionY = positionY + playerPos.y;

					bool collision = false;
					for (int b = 0; b < brickCount; b++)
					{
						if (Collision(explosionX, explosionY, brick[b]->getX(), brick[b]->getY(), BRICK_SIZE))
						{
							collision = true;
							break;
						}
					}

					if (collision)
					{
						break;
					}

					if (i == range - 1)
					{
						explosionSprite->SetFrame(j * 4 + 16 + 4);
					}
					else
					{
						explosionSprite->SetFrame(j * 4 + 4);
					}
					explosionSprite->Draw(screen, playerPos.x + positionX - cameraX, playerPos.y + positionY);
					exploded = true;
					position += 64.0f;

				}
			}
		}
		else
		{
			startCountdown = false;
			exploded = false;
		}
	}
}

bool Bomb::Collision(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE)
{
	//cout << "Checking explosion at (" << x << "," << y
	//<< ") vs brick (" << tx << "," << ty << ")" << endl;
	return (explosionX < tx + otherSPRITE_SIZE && explosionY < ty + otherSPRITE_SIZE &&
		explosionX + SPRITE_SIZE > tx && explosionY + SPRITE_SIZE > ty);
}