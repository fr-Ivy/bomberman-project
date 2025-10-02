// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "Brick.h"
#include "Door.h"
#include "Enemy.h"
#include "Valcom.h"
#include <iostream>

void Game::Init()
{
	srand(static_cast<unsigned int>(time(0)));
	doorSprite = new Sprite(new Surface("assets/door.png"), 1);
	enemySprite1 = new Sprite(new Surface("assets/enemy1.png"), 11);

	map = new Map(); //On the heap memory
	player = new Player(screen);
	bomb = new Bomb(screen, player, map);
	door = new Door(doorSprite, screen);
	valcom1 = new Valcom(screen, enemySprite1, map, player, this);

	player->SetGamePtr(this);	
	player->SetMapPtr(map);
	player->SetDoorPtr(door);
	player->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
	
	bomb->SetGamePtr(this);
	bomb->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

	door->SetGamePtr(this);
	door->SetMapPtr(map);
	door->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
	valcom1->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

	for (int i = 0; i < levels * amountBricks; i++)
	{
		bricks[i] = new Brick(screen, bomb, map);
		bricks[i]->choosePos();
	}
	door->ChoosePosition();

	valcom1->chooseRandomPos();
}

void Game::deleteBrick(int index)
{
	if (index < 0 || index >= amountBricks * levels) return;
	if (!bricks[index]) return;

	//std::cout << "Before delete: bricks[" << index << "] = " << bricks[index] << "\n";
	delete bricks[index];
	bricks[index] = nullptr;
	//std::cout << "after delete: bricks[" << index << "] = " << bricks[index] << "\n";

}

void Game::Level0()
{
	for (int i = amountBricks * currentLevel; i < amountBricks * currentLevel + amountBricks; i++)
	{
		if (bricks[i])
		{
			bricks[i]->Draw();
		}
	}
}

void Game::Level1()
{
	for (int i = amountBricks * currentLevel; i < amountBricks * currentLevel + amountBricks; i++)
	{
		if (bricks[i])
		{
			bricks[i]->Draw();
		}
	}
}

void Game::Tick( float deltaTime )
{
	//cout << currentLevel << endl;
	screen->Clear(0x000000);
	map->RenderMap(screen);
	player->move(deltaTime);
	player->GoToNextLevel(deltaTime);
	valcom1->move(deltaTime);

	//map.CheckCollision();
	door->Draw();
	player->Draw();
	bomb->Draw(deltaTime);
	valcom1->Draw();

	switch (currentLevel)
	{
	case 0: Level0(); break;
	case 1: Level1(); break;
	}

}

void Game::KeyUp(int key)
{
	player->KeyUp(key);
}

void Game::KeyDown(int key)
{
	player->KeyDown(key);
}