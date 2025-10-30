#include "precomp.h"
#include "Bomb.h"
#include "Player.h"
#include "Brick.h"
#include "game.h"
#include <iostream>

#include "Audio.h"
#include "Enemy.h"

Bomb::Bomb(Surface* screen, Player* player, Player* otherPlayer, Map* map, Audio* audio) 
	: player(player), map(map), otherPlayer(otherPlayer), audio(audio)
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


void Bomb::Draw(Surface* surface, int const camera, float const deltaTime)
{
	for (int i = 0; i < MAX_BOMBS; i++)
	{
		BombStruct& bomb = bombs[i];
		if (!bomb.active)
		{
			bomb.position = { 0,0 };
		}
	}

	ePressed = player->Get_E();
	cameraX1 = static_cast<int>(map->getCamera(camera));
	cameraX2 = static_cast<int>(map->getCamera(0));
	currentPlayerPos1 = player->getPos();
	currentPlayerPos2 = otherPlayer->getPos();

	//if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
	//{
	//	e_pressed = true;
	//}

	if (ePressed && !ePreviouslyPressed)
	{
		audio->Play(audio->placeBombSound);
		for (int i = 0; i < MAX_BOMBS; i++)
		{
			if (!bombs[i].active && isUsed[i])
			{
				BombStruct& bomb = bombs[i];
				bomb.active = true;
				bomb.bombCountdown = 3.0f;
				bomb.explosionCountdown = 1.0f;
				bomb.frame = 0;
				bomb.currentFrame = 0;
				bomb.frameCountdown = 0.4f;
				bomb.explosionFrameCountdown = 0.15f;
				bomb.explodingLevel = 1;

				playerPos = player->getPos();
				cameraX2 = 64;
				playerPos.x = (playerPos.x + cameraX2) / 64 * 64 - startPosX;
				playerPos.y = playerPos.y / 64 * 64;
				bomb.position = playerPos;
				break;
			}
		}
	}

	ePreviouslyPressed = ePressed;

	for (int currBomb = 0; currBomb < MAX_BOMBS; currBomb++)
	{
		BombStruct& bomb = bombs[currBomb];
		if (bomb.active && isUsed[currBomb])
		{
			if (bomb.bombCountdown >= 0.0f)
			{
				bomb.bombCountdown -= deltaTime;

				bombSprite->SetFrame(bomb.frame);
				bombSprite->Draw(surface, bomb. position.x - cameraX1, bomb.position.y);
				//cout << "cameraX: " << cameraX << endl;

				bomb.frameCountdown -= deltaTime;

				if (bomb.frameCountdown <= 0.0f)
				{
					bomb.frame = (bomb.frame + 1) % 3;
					bomb.frameCountdown = 0.4f;
				}

				//collision

				//cout << "bombCountdown: " << bombCountdown << endl;
			}
			else if (explosionSprite && bomb.explosionCountdown >= 0.0f)
			{
				bomb.explosionCountdown -= deltaTime;
				bomb.explosionFrameCountdown -= deltaTime;

				if (bomb.explosionFrameCountdown <= 0.0f)
				{
					if (bomb.currentFrame <= 0)
					{
						bomb.explodingLevel = 1;
					}
					else if (bomb.currentFrame >= 3)
					{
						bomb.explodingLevel = -1;
					}
					bomb.currentFrame += bomb.explodingLevel;
					bomb.explosionFrameCountdown = s_frameCooldown;
				}

				explosionSprite->SetFrame(bomb.currentFrame);
				//getExplosionMask(currentFrame, playerPos.x, playerPos.y);
				explosionSprite->Draw(surface, bomb.position.x - cameraX1, bomb.position.y);


				//resetBrickFrame = false;

				int2 directions[4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

				for (int j = 0; j < 4; j++) //drawing to every direction
				{
					int position = 64;

					for (int i = 0; i < range; i++, position += 64) // change range
					{
						int positionX = position * directions[j].x;
						int positionY = position * directions[j].y;
						int explosionX = positionX + bomb.position.x;
						int	explosionY = positionY + bomb.position.y;
						bool collision = false;
						for (int b = game->currentLevel * brickCount; b < brickCount * game->currentLevel + brickCount; b++)
						{
							if (brick[b] && Collision(explosionX, explosionY, brick[b]->getX(), brick[b]->getY(), BRICK_SIZE))
							{
								//play animation before deleting the brick (animation should be in the brick class) 
								//foundBrick = true;
								//brick[b]->startAnimation = true;

								/*if (brick[b]->animationEnded)
								{
									bomb.explosionCountdown = -1.0f;
									//foundBrick = false;
									game->DeleteBrick(b);
								} */
								collision = true;
							}

							if (/*(brick[b] && Collision(explosionX, explosionY, brick[b]->getX(), brick[b]->getY(), BRICK_SIZE)) ||*/
								map->CheckCollision(explosionX, explosionY))
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
							explosionSprite->SetFrame(j * 4 + 16 + 4 + bomb.currentFrame);
							GetExplosionMask(j * 4 + 16 + 4 + bomb.currentFrame);

						}
						else
						{
							explosionSprite->SetFrame(j * 4 + 4 + bomb.currentFrame);
							GetExplosionMask(j * 4 + 4 + bomb.currentFrame);
						}

						//getExplosionMask(currentFrame, playerPos.x, playerPos.y);

						explosionSprite->Draw(surface, bomb.position.x + positionX - cameraX1, bomb.position.y + positionY);


						//players
						if (TheCollisionPlayer(explosionX, explosionY, currentPlayerPos1.x, currentPlayerPos1.y, PLAYER_SPRITE, player))
						{
							player->startDyingAnimation = true;
						}
						if (TheCollisionPlayer(bomb.position.x, bomb.position.y, currentPlayerPos1.x, currentPlayerPos1.y, PLAYER_SPRITE, player))
						{
							player->startDyingAnimation = true;
						}
						if (TheCollisionPlayer(explosionX, explosionY, currentPlayerPos2.x, currentPlayerPos2.y, PLAYER_SPRITE, otherPlayer))
						{
							otherPlayer->startDyingAnimation = true;
						}
						if (TheCollisionPlayer(bomb.position.x, bomb.position.y, currentPlayerPos2.x, currentPlayerPos2.y, PLAYER_SPRITE, otherPlayer))
						{
							otherPlayer->startDyingAnimation = true;
						}

						for (int v = 0; v < 9; v++)
						{
							//enemies
							if (valcom[v] && valcom[v]->inLevel)
							{
								if (TheCollisionEnemy(explosionX, explosionY, static_cast<int>(valcom[v]->x), static_cast<int>(valcom[v]->y), PLAYER_SPRITE, valcom[v]))
								{
									valcom[v]->startDyingAnimation = true;
									//valcom[v]->deleteObject = true;
								}
								if (TheCollisionEnemy(bomb.position.x, bomb.position.y, static_cast<int>(valcom[v]->x), static_cast<int>(valcom[v]->y), PLAYER_SPRITE, valcom[v]))
								{
									valcom[v]->startDyingAnimation = true;
									//valcom[v]->deleteObject = true;
								}
							}
						}

						for (int o = 0; o < 3; o++)
						{
							if (oneal[o] && oneal[o]->inLevel)
							{
								if (TheCollisionEnemy(explosionX, explosionY, static_cast<int>(oneal[o]->x), static_cast<int>(oneal[o]->y), PLAYER_SPRITE, oneal[o]))
								{
									oneal[o]->startDyingAnimation = true;
									//oneal[o]->deleteObject = true;
								}
								if (TheCollisionEnemy(bomb.position.x, bomb.position.y, static_cast<int>(oneal[o]->x), static_cast<int>(oneal[o]->y), PLAYER_SPRITE, oneal[o]))
								{
									oneal[o]->startDyingAnimation = true;
									//oneal[o]->deleteObject = true;
								}
							}
						}
					}

						//exploded = true;
					audio->Play(audio->explosionSound);
				}
			}
			else
			{
				bomb.active = false;
				//startCountdown = false;
				//exploded = false;
				//playerCollision = false;
				//currentFrame = 0;
				//resetBrickFrame = true;
			}
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


bool Bomb::PlayerExplosionCollision(int const explosionX, int const explosionY, int const tx, int const ty, int const otherSPRITE_SIZE, Player* thePlayer)
{
	int playerLeft = tx;
	int const playerRight = tx + otherSPRITE_SIZE;
	int playerTop = ty;
	int const playerBottom = ty + otherSPRITE_SIZE;

	int explosionLeft = explosionX;
	int const explosionRight = explosionX + SPRITE_SIZE;
	int explosionTop = explosionY;
	int const explosionBottom = explosionY + SPRITE_SIZE;

	int const left = Max(playerLeft, explosionLeft);
	int const right = Min(playerRight, explosionRight);
	int const top = Max(playerTop, explosionTop);
	int const bottom = Min(playerBottom, explosionBottom);
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
			if (thePlayer->pixelVisible[(playerLeft + x) + (playerTop + y) * otherSPRITE_SIZE] &&
				explosionPixelVisible[(explosionLeft + x) + (explosionTop + y) * SPRITE_SIZE])
			{
				//cout << "hit" << endl;
#ifdef _DEBUG
				game->screen->Plot(left + x, top + y, 0x002880);
				game->screen2->Plot(left + x, top + y, 0x002880);
#endif
				hit = true;
			}
		}
	}
	return hit;

	//recources: https://croakingkero.com/tutorials/pixel_collision_detection/
}

bool Bomb::TheCollisionPlayer(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE, Player* thePlayer)
{
	if (Collision(explosionX, explosionY, tx, ty, otherSPRITE_SIZE))
	{
		thePlayer->Pixel(thePlayer->frame);
		//cout << "player hit explosion" << endl;
		if (PlayerExplosionCollision(explosionX, explosionY, tx, ty, otherSPRITE_SIZE, thePlayer))
		{
			return true;
			//player->ResetPosition();
		}
	}
	return false;
}

bool Bomb::TheCollisionEnemy(int explosionX, int explosionY, int tx, int ty, int otherSPRITE_SIZE, Enemy* theEnemy)
{
	if (Collision(explosionX, explosionY, tx, ty, otherSPRITE_SIZE))
	{
		theEnemy->Pixel(theEnemy->frame);
		//cout << "player hit explosion" << endl;
		if (EnemyExplosionCollision(explosionX, explosionY, tx, ty, otherSPRITE_SIZE, theEnemy))
		{
			return true;
			//player->ResetPosition();
		}
	}
	return false;
}


bool Bomb::EnemyExplosionCollision(int const explosionX, int const explosionY, int const tx, int const ty, int const otherSPRITE_SIZE, Enemy* theEnemy)
{
	int enemyLeft = tx;
	int const enemyRight = tx + otherSPRITE_SIZE;
	int enemyTop = ty;
	int const enemyBottom = ty + otherSPRITE_SIZE;

	int explosionLeft = explosionX;
	int const explosionRight = explosionX + SPRITE_SIZE;
	int explosionTop = explosionY;
	int const explosionBottom = explosionY + SPRITE_SIZE;

	int const left = Max(enemyLeft, explosionLeft);
	int const right = Min(enemyRight, explosionRight);
	int const top = Max(enemyTop, explosionTop);
	int const bottom = Min(enemyBottom, explosionBottom);
	int const columns = right - left;
	int const rows = bottom - top;
	//cout << "columns: " << columns << ", rows: " << rows << endl;

	enemyLeft = left - enemyLeft;
	enemyTop = top - enemyTop;
	explosionLeft = left - explosionLeft;
	explosionTop = top - explosionTop;

	bool hit = false;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			if (theEnemy->enemyPixelVisible[(enemyLeft + x) + (enemyTop + y) * otherSPRITE_SIZE] &&
				explosionPixelVisible[(explosionLeft + x) + (explosionTop + y) * SPRITE_SIZE])
			{
				//cout << "hit" << endl;
#ifdef _DEBUG
				game->screen->Plot(left + x, top + y, 0x002880);
				game->screen2->Plot(left + x, top + y, 0x002880);
#endif
				hit = true;
			}
		}
	}
	return hit;

	//recources: https://croakingkero.com/tutorials/pixel_collision_detection/
}