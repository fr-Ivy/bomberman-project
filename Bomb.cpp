#include "precomp.h"
#include "Bomb.h"
#include "Player.h"
#include "Brick.h"
#include "game.h"
#include <iostream>

Bomb::Bomb(Surface* screen, Player* player, Player* otherPlayer, Map* map) 
	: player(player), map(map), otherPlayer(otherPlayer)
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


void Bomb::Draw(Surface* surface, int camera, float const deltaTime)
{
	ePressed = player->Get_E();
	cameraX1 = map->getCamera(camera);
	cameraX2 = map->getCamera(0);
	currentPlayerPos1 = player->getPos();
	currentPlayerPos2 = otherPlayer->getPos();

	//if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
	//{
	//	e_pressed = true;
	//}

	if (ePressed && !startCountdown)
	{
		startCountdown = true;
		bombCountdown = 3.0f;
		explosionCountdown = 1.0f;
		playerPos1 = player->getPos();
		playerPos2 = otherPlayer->getPos();
		cameraX2 = 64;
		playerPos1.x = (playerPos1.x + cameraX2) / 64 * 64 - startPosX;
		playerPos1.y = playerPos1.y / 64 * 64;
	}

	if (bombSprite && startCountdown)
	{
		if (bombCountdown >= 0.0f)
		{
			bombCountdown -= deltaTime;

			bombSprite->Draw(surface, playerPos1.x - cameraX1, playerPos1.y);
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
			//getExplosionMask(currentFrame, playerPos.x, playerPos.y);
			explosionSprite->Draw(surface, playerPos1.x - cameraX1, playerPos1.y);


			//resetBrickFrame = false;

			int2 directions[4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

			for (int j = 0; j < 4; j++) //drawing to every direction
			{
				float position = 64.0f;

				for (int i = 0; i < range; i++, position += 64.0f) // change range
				{
					int positionX = position * directions[j].x;
					int positionY = position * directions[j].y;
					int explosionX = positionX + playerPos1.x;
					int	explosionY = positionY + playerPos1.y;
					bool collision = false;
					for (int b = game->currentLevel * brickCount; b < brickCount * game->currentLevel + brickCount; b++)
					{
						if (brick[b] && Collision(explosionX, explosionY, brick[b]->getX(), brick[b]->getY(), BRICK_SIZE))
						{
							//play animation before deleting the brick (animation should be in the brick class) 
							//foundBrick = true;
							brick[b]->playAnimation(deltaTime, resetBrickFrame);

							if (brick[b]->animationEnded)
							{
								explosionCountdown = -1.0f;
								//foundBrick = false;
								game->DeleteBrick(b);
							}
							
						}

						if ((brick[b] && Collision(explosionX, explosionY, brick[b]->getX(), brick[b]->getY(), BRICK_SIZE)) ||
							map->CheckCollision(0, explosionX - cameraX2, explosionY))
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
						GetExplosionMask(j * 4  + 16 + 4 + currentFrame);

					}
					else
					{
						explosionSprite->SetFrame(j * 4 + 4 + currentFrame);
						GetExplosionMask(j * 4 + 4 + currentFrame);
					}

					//getExplosionMask(currentFrame, playerPos.x, playerPos.y);

					explosionSprite->Draw(surface, playerPos1.x + positionX - cameraX1, playerPos1.y + positionY);

					if (Collision(explosionX - cameraX2, explosionY, currentPlayerPos1.x, currentPlayerPos1.y, PLAYER_SPRITE) ||
						Collision(playerPos1.x - cameraX2, playerPos1.y, currentPlayerPos1.x, currentPlayerPos1.y, PLAYER_SPRITE))
					{
						//cout << "player hit explosion" << endl;
						if (PlayerExplosionCollision(explosionX - cameraX2, explosionY, currentPlayerPos1.x, currentPlayerPos1.y, PLAYER_SPRITE) ||
							PlayerExplosionCollision(playerPos1.x - cameraX2, playerPos1.y, currentPlayerPos1.x, currentPlayerPos1.y, PLAYER_SPRITE))
						{
							//reset currentplayer pos
						}
					}

					if (Collision(explosionX - cameraX2, explosionY, currentPlayerPos2.x, currentPlayerPos2.y, PLAYER_SPRITE) ||
						Collision(playerPos1.x - cameraX2, playerPos1.y, currentPlayerPos2.x, currentPlayerPos2.y, PLAYER_SPRITE))
					{
						//cout << "player hit explosion" << endl;
						if (PlayerExplosionCollision(explosionX - cameraX2, explosionY, currentPlayerPos2.x, currentPlayerPos2.y, PLAYER_SPRITE) ||
							PlayerExplosionCollision(playerPos1.x - cameraX2, playerPos1.y, currentPlayerPos2.x, currentPlayerPos2.y, PLAYER_SPRITE))
						{
							//reset otherplayer pos
						}
					}

					//exploded = true;
				}
			}
		}
		else
		{
			startCountdown = false;
			//exploded = false;
			playerCollision = false;
			currentFrame = 0;
			//resetBrickFrame = true;
		}
	}
}

bool Bomb::Collision(int const explosionX, int const explosionY, int const tx, int const ty, int const otherSPRITE_SIZE)
{
	//cout << "Checking explosion at (" << x << "," << y
	//<< ") vs player or brick (" << tx << "," << ty << ")" << endl;
	return (explosionX < tx + otherSPRITE_SIZE && explosionY < ty + otherSPRITE_SIZE &&
		explosionX + SPRITE_SIZE > tx && explosionY + SPRITE_SIZE > ty);
}

void Bomb::GetExplosionMask(int const frameNumber)
{
	uint32_t* pixels = explosionSprite->GetBuffer();
	int frameOffset = frameNumber * SPRITE_SIZE;

	for (int y = 0; y < SPRITE_SIZE; y++)
	{
		for (int x = 0; x < SPRITE_SIZE; x++)
		{
			uint32_t pixel = pixels[x + frameOffset + y * SPRITE_SIZE * 36];
			explosionPixelVisible[x + y * SPRITE_SIZE] = (pixel != 0);
			bool visible = explosionPixelVisible[x + y * SPRITE_SIZE];
			if (visible)
			{
				//screen->Plot(explosionX + x - cameraX, explosionY + y, 0x000000);
			}
		}
	}
}


bool Bomb::PlayerExplosionCollision(int const explosionX, int const explosionY, int const tx, int const ty, int const otherSPRITE_SIZE) const
{
	int playerLeft = tx;
	int const playerRight = tx + otherSPRITE_SIZE;
	int playerTop = ty;
	int const playerBottom = ty + otherSPRITE_SIZE;

	int explosionLeft = explosionX;
	int const explosionRight = explosionX + SPRITE_SIZE;
	int explosionTop = explosionY;
	int const explosionBottom = explosionY + SPRITE_SIZE;

	int const left = max(playerLeft, explosionLeft);
	int const right = min(playerRight, explosionRight);
	int const top = max(playerTop, explosionTop);
	int const bottom = min(playerBottom, explosionBottom);
	int const columns = right - left;
	int const rows = bottom - top;
	//cout << "columns: " << columns << ", rows: " << rows << endl;

	playerLeft = left - playerLeft;
	playerTop = top - playerTop;
	explosionLeft = left - explosionLeft;
	explosionTop = top - explosionTop;

	bool hit = false;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			if (player->pixelVisible[(playerLeft + x) + (playerTop + y) * otherSPRITE_SIZE] &&
				explosionPixelVisible[(explosionLeft + x) + (explosionTop + y) * SPRITE_SIZE])
			{
				//cout << "hit" << endl;
				game->screen1->Plot(left + x, top + y, 0x002880);
				game->screen2->Plot(left + x, top + y, 0x002880);
				hit = true;
			}
		}
	}
	return hit;

	//recources: https://croakingkero.com/tutorials/pixel_collision_detection/
}
