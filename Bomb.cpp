#include "precomp.h"
#include "Bomb.h"
#include "Player.h"
#include "Brick.h"
#include "game.h"
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
	currentPlayerPos = player->getPos();

	//if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
	//{
	//	e_pressed = true;
	//}

	if (e_pressed && !startCountdown)
	{
		startCountdown = true;
		bombCountdown = 3.0f;
		explosionCountdown = 10.0f;
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
			explosionFrameCountdown -= deltaTime;

			if (explosionFrameCountdown <= 0.0f)
			{
				if (currentFrame <= 0)
				{
					explodingLevel = 1;
				}
				else if (currentFrame >= 3)
				{
					explodingLevel = -1;
				}
				currentFrame = currentFrame + explodingLevel;
				explosionFrameCountdown = s_frameCooldown;
			}



			explosionSprite->SetFrame(currentFrame);
			explosionSprite->Draw(screen, playerPos.x - cameraX, playerPos.y);

			resetBrickFrame = false;

			int2 directions[4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

			for (int j = 0; j < 4; j++) //drawing to every direction
			{
				float position = 64.0f;

				for (int i = 0; i < range; i++, position += 64.0f) // change range
				{
					int positionX = position * directions[j].x;
					int positionY = position * directions[j].y;
					int explosionX = positionX + playerPos.x;
					int	explosionY = positionY + playerPos.y;
					bool collision = false;
					for (int b = game->currentLevel * brickCount; b < brickCount * game->currentLevel + brickCount; b++)
					{
						if (brick[b] && Collision(explosionX, explosionY, brick[b]->getX(), brick[b]->getY(), BRICK_SIZE))
						{
							//play animation before deleting the brick (animation should be in the brick class) 

							brick[b]->playAnimation(deltaTime, resetBrickFrame);

							if (brick[b]->animationEnded)
							{
								game->deleteBrick(b);
							}
						}


						if ((brick[b] && Collision(explosionX, explosionY, brick[b]->getX(), brick[b]->getY(), BRICK_SIZE)) ||
							map->CheckCollision(explosionX - cameraX, explosionY))
						{
							collision = true;
						}
					}

					//cout << "Player pos: " << currentPlayerPos.x << ", " << currentPlayerPos.y << endl;
					//cout << "Explosion pos: " << explosionX << ", " << explosionY << endl;


					if (collision)
					{
						break;
					}

					if (i == range - 1)
					{
						explosionSprite->SetFrame(j * 4 + 16 + 4 + currentFrame);
					}
					else
					{
						explosionSprite->SetFrame(j * 4 + 4 + currentFrame);
					}

					getExplosionMask(currentFrame);

					explosionSprite->Draw(screen, playerPos.x + positionX - cameraX, playerPos.y + positionY);

					if (Collision(explosionX - cameraX, explosionY, currentPlayerPos.x, currentPlayerPos.y, PLAYER_SPRITE) ||
						Collision(playerPos.x + positionX - cameraX, playerPos.y + positionY, currentPlayerPos.x, currentPlayerPos.y, PLAYER_SPRITE))
					{
						if (PlayerExplosionCollision(explosionX - cameraX, explosionY, currentPlayerPos.x, currentPlayerPos.y, PLAYER_SPRITE) ||
							PlayerExplosionCollision(playerPos.x + positionX - cameraX, playerPos.y + positionY, currentPlayerPos.x, currentPlayerPos.y, PLAYER_SPRITE))
						{

						}
					}

					exploded = true;
				}
			}
		}
		else
		{
			startCountdown = false;
			exploded = false;
			playerCollision = false;
			currentFrame = 0;
			resetBrickFrame = true;
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

void Bomb::getExplosionMask(int frameNumber)
{
	uint* pixels = explosionSprite->GetBuffer();
	int frameOffset = frameNumber * SPRITE_SIZE * SPRITE_SIZE;

	for (int y = 0; y < SPRITE_SIZE; y++)
		for (int x = 0; x < SPRITE_SIZE; x++)
			ExplosionPixelVisible[x + y * SPRITE_SIZE] = (pixels[x + y * SPRITE_SIZE + frameOffset] != 0);
}


bool Bomb::PlayerExplosionCollision(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE)
{
	int playerLeft = tx;
	int playerRight = tx + otherSPRITE_SIZE;
	int playerTop = ty;
	int playerBottom = ty + otherSPRITE_SIZE;

	int explosionLeft = explosionX;
	int explosionRight = explosionX + SPRITE_SIZE;
	int explosionTop = explosionY;
	int explosionBottom = explosionY + SPRITE_SIZE;

	int left = max(playerLeft, explosionLeft);
	int right = min(playerRight, explosionRight);
	int top = max(playerTop, explosionTop);
	int bottom = min(playerBottom, explosionBottom);
	int columns = right - left;
	int rows = bottom - top;
	//std::cout << "columns=" << columns << ", rows=" << rows << std::endl;

	if (columns <= 0 || rows <= 0) return false;

	playerLeft = left - playerLeft;
	playerTop = top - playerTop;
	explosionLeft = left - explosionLeft;
	explosionTop = top - explosionTop;

	int hit = false;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			if (player->pixelVisible[(playerLeft + x) + (playerTop + y) * otherSPRITE_SIZE] &&
				ExplosionPixelVisible[(explosionLeft + x) + (explosionTop + y) * SPRITE_SIZE])
			{
				//cout << "hit" << endl;
				screen->Plot(left + x, top + y, 0x002880);
				hit = true;
			}
		}
	}
	return hit;
}
