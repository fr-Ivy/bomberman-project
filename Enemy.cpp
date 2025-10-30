#include "precomp.h"
#include "Enemy.h"
#include "map.h"
#include "Brick.h"
#include "Bomb.h"
#include <iostream>

//https://www.linkedin.com/pulse/understanding-c-references-passing-custom-classes-towfik-alrazihi#:~:text=Pass%20by%20Reference%3A%20The%20Basics&text=To%20pass%20a%20custom%20class,in%20the%20function%20parameter%20declaration.&text=In%20this%20example%2C%20the%20modifyObject,directly%20affect%20the%20original%20myObject.

Enemy::Enemy(Surface* screen, Sprite* enemySprite, Map& map, Player& player1, Player& player2, Game* game, int points)
	: map(map), player1(player1), game(game), player2(player2), points(points)
{
	this->screen = screen;
	this->enemySprite = enemySprite;
}

void Enemy::CheckBrickCollision(int px, int py)
{
	brickCollision = false;
	for (int i = game->currentLevel * brickCount; i < brickCount * game->currentLevel + brickCount; i++)
	{
		//check collision for each dir
		if (brick[i] && brick[i]->checkCollision(px, py, SPRITE_SIZE))
		{
			//cout << "hit" << endl;
			brickCollision = true;
		}
		else
		{
			//cout << "not hit" << endl;
			//cout << x << ", " << y << endl;
		}

		if (!brick[i])
		{
			//cout << "no brick:" << brick[i] << endl;
		}
	}
	//cout << "Check Func" << endl;
}

void Enemy::Draw(Surface* surface, int camera)
{
	cameraX1 = map.getCamera(camera); //
	screenX = x - cameraX1;


	if (dying)
	{
		enemySprite->SetFrame(dyingFrame + 6);
	}
	else
	{
		enemySprite->SetFrame(frame);
	}
	enemySprite->Draw(surface, static_cast<int>(screenX), static_cast<int>(y));
	Pixel(0);
}

bool Enemy::CheckStartPos(int const cx, int const cy) const
{
	int px = cx / TILE_SIZE;
	int py = cy / TILE_SIZE;

	for (int tx2 = 1; tx2 <= 4; tx2++)
	{
		for (int ty2 = 1; ty2 <= 4; ty2++)
		{
			if ((px == tx2 && py == ty2) || (px == tx2 + 25 && py == ty2))
				return false;
		}
	}
	return true;
}

void Enemy::ChooseRandomPos()
{
	do
	{
		x = static_cast<float>(rand() % (mapWidth / 64) * 64);
		y = static_cast<float>(rand() % (mapHeight / 64) * 64);
		CheckBrickCollision(static_cast<int>(x), static_cast<int>(y));
	} while (map.CheckCollision(static_cast<int>(x), static_cast<int>(y)) || brickCollision || !CheckStartPos(static_cast<int>(x), static_cast<int>(y)));
	//cout << x << ", " << y << endl;
}

bool Enemy::CheckCorners(int const x1, int const y1, int const x2, int const y2) const
{
	return map.CheckCollision(x1, y1) && map.CheckCollision(x2, y2);
}

void Enemy::BackToTile()
{
	int px = static_cast<int>(tx);
	//cout << px << endl;

	if (px % TILE_SIZE >= 32)
	{
		px = px / TILE_SIZE * TILE_SIZE + TILE_SIZE;

	}
	else
	{
		px = px / TILE_SIZE * TILE_SIZE;

	}
	tx = static_cast<float>(px);


	int py = static_cast<int>(ty);
	//cout << py << endl;

	if (py % TILE_SIZE >= 32)
	{
		py = (py / TILE_SIZE) * TILE_SIZE + TILE_SIZE;

	}
	else
	{
		py = (py / TILE_SIZE) * TILE_SIZE;

	}
	ty = static_cast<float>(py);
}

void Enemy::Move(float const /* deltaTime */)
{
	cout << "should never be reached" << endl;
}

void Enemy::WalkingAnitmation(float deltaTime)
{
	walkingFrameCountdown -= deltaTime;

	if (walkingFrameCountdown <= 0.0f)
	{
		frame = (frame + 1) % 6;
		walkingFrameCountdown = 0.3f;
	}
}

void Enemy::DyingAnimation(float deltaTime)
{
	//cout << startDyingAnimation << endl;
	if (startDyingAnimation)
	{
		if (dyingFrame < 5)
		{
			//playerSprite->SetFrame(dyingFrame + 12);
			dying = true;
		}

		dyingFrameCountdown -= deltaTime;

		if (dyingFrameCountdown <= 0.0f)
		{
			dyingFrame = (dyingFrame + 1) % 6;
			dyingFrameCountdown = 3.0f / 7.0f;
		}

		if (dyingFrame >= 5)
		{
			startDyingAnimation = false;
			deleteObject = true;
			dyingFrame = 0;
			dying = false;
			game->score += points;
		}
	}
}

void Enemy::Pixel(int const frameNumber)
{
	const uint32_t* pixels = enemySprite->GetBuffer();
	int frameOffset = frameNumber * SPRITE_SIZE;

	for (int ty2 = 0; ty2 < SPRITE_SIZE; ty2++)
	{
		for (int tx2 = 0; tx2 < SPRITE_SIZE; tx2++)
		{
			const uint32_t pixel = pixels[tx2 + frameOffset + ty2 * SPRITE_SIZE * 11];
			enemyPixelVisible[tx2 + ty2 * SPRITE_SIZE] = (pixel != 0);
			bool visible = enemyPixelVisible[tx2 + ty2 * SPRITE_SIZE];
			if (visible)
			{
				//surface->Plot(x + tx - cameraX1, y + ty, 0xFF0000);
			}
		}
	}
}

bool Enemy::BombCollision() const
{
	int hit = false;
	for (int i = 0; i < bomb1->MAX_BOMBS; i++)
	{
		if (bomb1->Collision(bomb1->bombs[i].position.x, bomb1->bombs[i].position.y, static_cast<int>(tx), static_cast<int>(ty), SPRITE_SIZE) || 
			bomb2->Collision(bomb2->bombs[i].position.x, bomb2->bombs[i].position.y, static_cast<int>(tx), static_cast<int>(ty), SPRITE_SIZE))
		{
			hit = true;
		}
	}
	return hit;
}
