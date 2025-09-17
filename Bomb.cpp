#include "precomp.h"
#include "Bomb.h"
#include "Player.h"
#include <iostream>

Bomb::Bomb(Sprite* spriteBomb, Sprite* spriteExplosion, Surface* screen, Player* player, Map* map) 
	: player_(player), map_(map)
{
	this->screen = screen;
	this->spriteBomb = spriteBomb;
	this->spriteExplosion = spriteExplosion;
}


void Bomb::Draw(float deltaTime)
{
	deltaTime /= 1000.0f;
	e_pressed = player_->Get_E();
	cameraX = map_->getCamera();

	//if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
	//{
	//	e_pressed = true;
	//}

	if (e_pressed && !startCountdown)
	{
		startCountdown = true;
		bombCountdown = 3.0f;
		explosionCountdown = 1.0f;
		playerPos = player_->getPos();
		cameraX = playerPos.x;
		playerPos.x = playerPos.x + cameraX - startPosX;
	}

	if (spriteBomb && startCountdown)
	{
		if (bombCountdown >= 0.0f)
		{
			bombCountdown -= deltaTime;

			spriteBomb->Draw(screen, (playerPos.x) - cameraX, playerPos.y);
			cout << "cameraX: " << cameraX << endl;
			spriteBomb->SetFrame(frame);

			frameCountdown -= deltaTime;

			if (frameCountdown <= 0.0f)
			{
				frame = (frame + 1) % 3;
				frameCountdown = 0.4f;
			}

			//cout << "bombCountdown: " << bombCountdown << endl;
		}
		else if (spriteExplosion && explosionCountdown >= 0.0f)
		{
			explosionCountdown -= deltaTime;
			spriteExplosion->Draw(screen, (playerPos.x) - cameraX, playerPos.y);

			int2 directions[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

			int index = 1;
			//index <= 4

			float position = 64.0f;

			for (int i = 1; i <= 4; i++) // change position
			{
				for (int j = 0; j < 4; j++) //drawing to every direction
				{
					int positionX = position * i * directions[j].x;
					int positionY = position * i * directions[j].y;
					spriteExplosion->Draw(screen, playerPos.x + positionX - cameraX, playerPos.y + positionY);
				}
				position += 64.0f;
			}

			//spriteExplosion
		}
		else
		{
			startCountdown = false;
			//bombCountdown = 3.0f;
		}
	}
}

