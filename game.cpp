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
#include <iostream>

void Game::Init()
{
	doorSprite = new Sprite(new Surface("assets/door.png"), 1);

	player = new Player(screen);
	map = new Map(); //On the heap memory
	bomb = new Bomb(screen, player, map);
	door = new Door(doorSprite, screen);


	for (int i = 0; i < levels * amountBricks; i++)
	{
		bricks[i] = new Brick(screen, bomb, map);
		bricks[i]->choosePos();
	}

	player->SetMapPtr(map);
	player->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
	bomb->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
	bomb->SetGamePtr(this);
	player->SetGamePtr(this);
	door->SetGamePtr(this);
	door->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
	door->SetMapPtr(map);


	door->ChoosePosition();


	srand(static_cast<unsigned int>(time(0)));
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
	screen->Clear(0x000000);
	map->RenderMap(screen);
	player->move(deltaTime);

	//map.CheckCollision();
	door->Draw();
	player->Draw();
	bomb->Draw(deltaTime);

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