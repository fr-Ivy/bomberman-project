// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "Brick.h"

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

	srand(static_cast<unsigned int>(time(0)));
}


void Game::Tick( float deltaTime )
{
	screen->Clear(0x000000);
	map->RenderMap(screen);
	player->move(deltaTime);
	player->Draw();
	//map.CheckCollision();
	bomb->Draw(deltaTime);


	for (int i = 0; i < amountBricks; i++)
	{
		bricks[i]->Draw();
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