// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "Brick.h"
#include <iostream>

void Game::Init()
{
	player = new Player(screen);
	map = new Map(); //On the heap memory
	bomb = new Bomb(screen, player, map);

	for (int i = 0; i < amountBricks; i++)
	{
		bricks[i] = new Brick(screen, bomb, map);
		bricks[i]->choosePos();
	}

	player->SetMapPtr(map);
	player->SetBrickPtr(bricks, amountBricks);
	bomb->SetBrickPtr(bricks, amountBricks);
	bomb->SetGamePtr(this);

	srand(static_cast<unsigned int>(time(0)));
}

void Game::deleteBrick(int index)
{
	if (index < 0 || index >= amountBricks) return;
	if (!bricks[index]) return;

	std::cout << "Before delete: bricks[" << index << "] = " << bricks[index] << "\n";
	delete bricks[index];
	bricks[index] = nullptr;
	std::cout << "after delete: bricks[" << index << "] = " << bricks[index] << "\n";

}

void Game::Level1()
{
	for (int i = 0; i < amountBricks; i++)
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
	player->Draw();
	bomb->Draw(deltaTime);

	Level1();
}

void Game::KeyUp(int key)
{
	player->KeyUp(key);
}

void Game::KeyDown(int key)
{
	player->KeyDown(key);
}