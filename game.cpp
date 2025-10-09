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
	screen1 = new Surface(SCRWIDTH / 2, SCRHEIGHT);
	screen2 = new Surface(SCRWIDTH / 2, SCRHEIGHT);
	srand(static_cast<unsigned int>(time(nullptr)));
	doorSprite = new Sprite(new Surface("assets/door.png"), 1);
	enemySprite1 = new Sprite(new Surface("assets/enemy1.png"), 11);

	map = new Map(); //On the heap memory
	player[0] = new Player(screen1, 64, 64, 0);
	player[1] = new Player(screen2, 500, 64, 1);

	bomb[0] = new Bomb(screen1, player[0], player[1], map);
	bomb[1] = new Bomb(screen2, player[1], player[0], map);
	door = new Door(doorSprite, screen1);
	valcom1 = new Valcom(screen1, enemySprite1, map, player[0], player[1], this);

	player[0]->SetGamePtr(this);	
	player[0]->SetMapPtr(map);
	player[0]->SetDoorPtr(door);
	player[0]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

	player[1]->SetGamePtr(this);
	player[1]->SetMapPtr(map);
	player[1]->SetDoorPtr(door);
	player[1]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);


	bomb[0]->SetGamePtr(this);
	bomb[0]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

	bomb[1]->SetGamePtr(this);
	bomb[1]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

	door->SetGamePtr(this);
	door->SetMapPtr(map);
	door->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
	valcom1->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

	for (int i = 0; i < levels * amountBricks; i++)
	{
		bricks[i] = new Brick(screen1, screen2, bomb[0], map);
		bricks[i]->choosePos();
	}
	door->ChoosePosition();

	valcom1->ChooseRandomPos();
}

void Game::DeleteBrick(int const index)
{
	if (index < 0 || index >= amountBricks * levels) return;
	if (!bricks[index]) return;

	//cout << "Before delete: bricks[" << index << "] = " << bricks[index] << "\n";
	delete bricks[index];
	bricks[index] = nullptr;
	//cout << "after delete: bricks[" << index << "] = " << bricks[index] << "\n";

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
	deltaTime /= 1000.0f;
	//cout << currentLevel << endl;
	screen1->Clear(0x000000);
	screen2->Clear(0x000000);
	player[0]->move(deltaTime);
	player[0]->GoToNextLevel(deltaTime);
	player[1]->move(deltaTime);
	player[1]->GoToNextLevel(deltaTime);
	valcom1->Move(deltaTime);

	map->camera(0, player[0]->getX());
	map->camera(1, player[1]->getX());

	map->RenderMap(screen1, 0); //add the first camera here
	map->RenderMap(screen2, 1); //add the second camera here

	//map.CheckCollision();
	door->Draw();
	player[0]->Draw(screen1, map->getCamera(0), 1, 0);
	player[0]->Draw(screen2, map->getCamera(1), 1, 0);
	player[1]->Draw(screen1, map->getCamera(0), 1, 0);
	player[1]->Draw(screen2, map->getCamera(1), 1, 0);

	bomb[0]->Draw(screen1, 0, deltaTime);
	bomb[0]->Draw(screen2, 1, deltaTime);
	bomb[1]->Draw(screen1, 0, deltaTime);
	bomb[1]->Draw(screen2, 1, deltaTime);
	valcom1->Draw(screen1, 0);
	valcom1->Draw(screen2, 1);

	switch (currentLevel)
	{
	case 0: Level0(); break;
	case 1: Level1(); break;
	default: break;
	}

	screen1->CopyTo(screen, 0, 0);
	screen2->CopyTo(screen, SCRWIDTH / 2, 0);
	//screen->CopyTo(screen, 640, 0);
}

void Game::KeyUp(int const key)
{
	player[0]->KeyUpWASD(key);
	player[1]->KeyUpARROWS(key);
}

void Game::KeyDown(int const key)
{
	player[0]->KeyDownWASD(key);
	player[1]->KeyDownARROWS(key);
}