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
#include "O_Neal.h"
#include "Power_ups.h"
#include "ExtraFlameRange.h"
#include "ExtraBomb.h"
#include "UI.h"
#include "Arrow.h"
#include <iostream>

#include "Audio.h"

#ifdef _DEBUG
//#include <vld.h>
#endif


Game::~Game()
{
	//delete[] bricks;
}

void Game::Init()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	screen1 = new Surface(SCRWIDTH / 2, SCRHEIGHT);
	screen2 = new Surface(SCRWIDTH / 2, SCRHEIGHT);
	doorSprite = new Sprite(new Surface("assets/door.png"), 1);
	valcomSprite = new Sprite(new Surface("assets/enemy1.png"), 11);
	ONealSprite = new Sprite(new Surface("assets/ONeal.png"), 11);
	extraFlameRangeSprite = new Sprite(new Surface("assets/power-ups/extraFlameRange.png"), 1);
	extraBombSprite = new Sprite(new Surface("assets/power-ups/extraBomb.png"), 1);

	map = new Map(this); //On the heap memory
	player[0] = new Player(screen1, 64, 64, 0);
	player[1] = new Player(screen2, 29 * 64, 64, 1);
	audio = new Audio();
	audio->Init();

	for (int i = 0; i < amountValcoms; i++)
	{
		valcom[i] = new Valcom(screen1, valcomSprite, *map, *player[0], *player[1], this, 100);
		//Do this the same as for the bricks
	}

	for (int i = 0; i < amountONeals; i++)
	{
		ONeal[i] = new O_Neal(screen1, ONealSprite, *map, *player[0], *player[1], this, 200);
	}
	bomb[0] = new Bomb(screen1, player[0], player[1], map, audio);
	bomb[1] = new Bomb(screen2, player[1], player[0], map, audio);
	door = new Door(doorSprite, screen1);
	extraFlameRange = new ExtraFlameRange(screen1, extraFlameRangeSprite, player[0], player[1], bomb[0], bomb[1], map);
	extraBomb = new ExtraBomb(screen1, extraBombSprite, player[0], player[1], bomb[0], bomb[1], map);


	for (int i = 0; i < levels * amountBricks; i++)
	{
		bricks[i] = new Brick(screen1, screen2, map);
		bricks[i]->choosePos();
	}

	player[0]->SetGamePtr(this);
	player[0]->SetMapPtr(map);
	player[0]->SetDoorPtr(door);
	player[0]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
	player[0]->setEnemyPtr(valcom, ONeal);
	player[0]->SetAudioPtr(audio);

	player[1]->SetGamePtr(this);
	player[1]->SetMapPtr(map);
	player[1]->SetDoorPtr(door);
	player[1]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
	player[1]->setEnemyPtr(valcom, ONeal);
	player[1]->SetAudioPtr(audio);


	bomb[0]->SetGamePtr(this);
	bomb[0]->setEnemyPtr(valcom, ONeal);
	bomb[0]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

	bomb[1]->SetGamePtr(this);
	bomb[1]->setEnemyPtr(valcom, ONeal);
	bomb[1]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

	door->SetGamePtr(this);
	door->SetMapPtr(map);
	door->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

	extraFlameRange->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
	extraBomb->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

	door->ChoosePosition();
	extraFlameRange->ChoosePos(0);
	extraBomb->ChoosePos(1);

	for (int i = 0; i < 9; i++)
	{
		valcom[i]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
		valcom[i]->SetBombPtr(bomb[0], bomb[1]);
		valcom[i]->ChooseRandomPos();
	}

	for (int i = 0; i < 3; i++)
	{
		ONeal[i]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
		ONeal[i]->SetBombPtr(bomb[0], bomb[1]);
		ONeal[i]->ChooseRandomPos();
	}

	menuScreen = new Surface("assets/UI/menu.png");
	gameOverScreen = new Surface("assets/UI/gameOver2.png");
	gameModeScreen = new Surface("assets/UI/choose_gamemode.png");
	controlsScreen = new Surface("assets/UI/controls2.png");
	menuArrow = new Sprite(new Surface("assets/UI/Arrow.png"), 1);

	menuUI = new UI(menuScreen, 250, 0);
	gameOverUI = new UI(gameOverScreen, 250, 0);
	gameModeUI = new UI(gameModeScreen, 250, 0);
	controlsUI = new UI(controlsScreen, 250, 0);
	arrow = new Arrow(menuArrow);
	arrow->SetGamePtr(this);
}

void Game::DeleteBrick(int const index)
{
	if (index < 0 || index >= amountBricks * levels) return;
	if (!bricks[index]) return;

	//cout << "Before delete: bricks[" << index << "] = " << bricks[index] << "\n";
	bricks[index] = nullptr;
	delete bricks[index];
	//cout << "after delete: bricks[" << index << "] = " << bricks[index] << "\n";
}

bool Game::AllFalse(int start1, int end1, int start2, int end2)
{
	for (int i = start1; i < end1; i++)
	{
		for (int j = start2; j < end2; j++)
		{
			if (valcom[i] && ONeal[j])
			{
				return false;
			}
		}
	}
	return true;
}


void Game::Level0(float deltaTime)
{
	if (gameMode == 2)
	{
		if (extraFlameRange)
		{
			extraFlameRange->Draw(screen1, 0);
		}

		for (int i = amountBricks * currentLevel; i < amountBricks * currentLevel + amountBricks; i++)
		{
			if (bricks[i])
			{
				bricks[i]->Draw(screen1, 0);
			}
		}
		if (extraFlameRange)
		{
			extraFlameRange->Draw(screen2, 1);
		}

		for (int i = amountBricks * currentLevel; i < amountBricks * currentLevel + amountBricks; i++)
		{
			if (bricks[i])
			{
				bricks[i]->Draw(screen2, 1);
			}
		}
	}

	if (gameMode == 1)
	{
		if (extraFlameRange)
		{
			extraFlameRange->Draw(screen, 2);
		}

		for (int i = amountBricks * currentLevel; i < amountBricks * currentLevel + amountBricks; i++)
		{
			if (bricks[i])
			{
				bricks[i]->Draw(screen, 2);
			}
		}
	}

	if (extraFlameRange)
	{
		extraFlameRange->Power();
	}



	if (AllFalse(0, 6, 0, 6))
	{
		if (player[0]->GoToNextLevel() || player[1]->GoToNextLevel())
		{
			player[0]->ResetPosition();
			player[1]->ResetPosition();
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (valcom[i])
		{
			if (!valcom[i]->startDyingAnimation)
			{
				valcom[i]->Move(deltaTime);
			}
			valcom[i]->inLevel = true;
		}


		if (valcom[i] && valcom[i]->MarkForDeletion())
		{
			delete valcom[i];
			valcom[i] = nullptr;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (valcom[i])
		{
			valcom[i]->Draw(screen, 2);
			valcom[i]->Draw(screen1, 0);
			valcom[i]->Draw(screen2, 1);
		}
	}
	audio->Play(audio->musicLvl1);
	audio->Stop(audio->musicLvl2);
}

void Game::Level1(float deltaTime)
{
	if (gameMode == 2)
	{
		if (extraBomb)
		{
			extraBomb->Draw(screen1, 0);
		}

		for (int i = amountBricks * currentLevel; i < amountBricks * currentLevel + amountBricks; i++)
		{
			if (bricks[i])
			{
				bricks[i]->Draw(screen1, 0);
			}
		}
		if (extraBomb)
		{
			extraBomb->Draw(screen2, 1);
		}

		for (int i = amountBricks * currentLevel; i < amountBricks * currentLevel + amountBricks; i++)
		{
			if (bricks[i])
			{
				bricks[i]->Draw(screen2, 1);
			}
		}
	}

	if (gameMode == 1)
	{
		if (extraBomb)
		{
			extraBomb->Draw(screen, 2);
		}

		for (int i = amountBricks * currentLevel; i < amountBricks * currentLevel + amountBricks; i++)
		{
			if (bricks[i])
			{
				bricks[i]->Draw(screen, 2);
			}
		}
	}

	if (extraBomb)
	{
		extraBomb->Power();
	}

	if (!AllFalse(6, 9, 0, 3))
	{
		if (player[0]->GoToNextLevel() || player[1]->GoToNextLevel())
		{
			player[0]->ResetPosition();
			player[1]->ResetPosition();
		}
	}

	for (int i = 6; i < 9; i++)
	{
		if (valcom[i])
		{
			valcom[i]->inLevel = true;
			if (!valcom[i]->startDyingAnimation)
			{
				valcom[i]->Move(deltaTime);
			}
		}


		if (valcom[i] && valcom[i]->MarkForDeletion())
		{
			delete valcom[i];
			valcom[i] = nullptr;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (ONeal[i])
		{
			ONeal[i]->inLevel = true;
			if (!ONeal[i]->startDyingAnimation)
			{
				ONeal[i]->Move(deltaTime);
			}
		}

		if (ONeal[i] && ONeal[i]->MarkForDeletion())
		{
			delete ONeal[i];
			ONeal[i] = nullptr;
		}
	}

	for (int i = 6; i < 9; i++)
	{
		if (valcom[i])
		{
			valcom[i]->Draw(screen, 2);
			valcom[i]->Draw(screen1, 0);
			valcom[i]->Draw(screen2, 1);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (ONeal[i])
		{
			ONeal[i]->Draw(screen, 2);
			ONeal[i]->Draw(screen1, 0);
			ONeal[i]->Draw(screen2, 1);
		}
	}
	audio->Play(audio->musicLvl2);
	audio->Stop(audio->musicLvl1);
}

void Game::Tick(float deltaTime)
{	deltaTime /= 1000.0f;

	if (pressedPlay)
	{
		bomb[0]->range = 1;
		bomb[1]->range = 1;
		bomb[0]->isUsed[1] = false;
		bomb[1]->isUsed[1] = false;

		for (int i = 0; i < amountBricks * levels; i++)
		{
			delete bricks[i];
			bricks[i] = nullptr;
			bricks[i] = new Brick(screen1, screen2, map);
			bricks[i]->choosePos();
		}

		for (int i = 0; i < amountValcoms; i++)
		{
			delete valcom[i];
			valcom[i] = nullptr;
			valcom[i] = new Valcom(screen, valcomSprite, *map, *player[0], *player[1], this, 100);
		}

		for (int i = 0; i < amountONeals; i++)
		{
			delete ONeal[i];
			ONeal[i] = nullptr;
			ONeal[i] = new O_Neal(screen, ONealSprite, *map, *player[0], *player[1], this, 200);
		}

		delete extraFlameRange;
		extraFlameRange = nullptr;
		extraFlameRange = new ExtraFlameRange(screen1, extraFlameRangeSprite, player[0], player[1], bomb[0], bomb[1], map);

		delete extraBomb;
		extraBomb = nullptr;
		extraBomb = new ExtraBomb(screen1, extraBombSprite, player[0], player[1], bomb[0], bomb[1], map);

		player[0]->setEnemyPtr(valcom, ONeal);
		player[1]->setEnemyPtr(valcom, ONeal);
		player[0]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
		player[1]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

		bomb[0]->setEnemyPtr(valcom, ONeal);
		bomb[0]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
		bomb[1]->setEnemyPtr(valcom, ONeal);
		bomb[1]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

		door->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
		extraFlameRange->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
		extraBomb->SetBrickPtr(bricks, amountBricks, amountBricks * levels);

		for (int i = 0; i < 9; i++)
		{
			valcom[i]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
			valcom[i]->SetBombPtr(bomb[0], bomb[1]);
			valcom[i]->ChooseRandomPos();
		}

		for (int i = 0; i < 3; i++)
		{
			ONeal[i]->SetBrickPtr(bricks, amountBricks, amountBricks * levels);
			ONeal[i]->SetBombPtr(bomb[0], bomb[1]);
			ONeal[i]->ChooseRandomPos();
		}

		door->ChoosePosition();
		extraFlameRange->ChoosePos(0);
		extraBomb->ChoosePos(1);


		player[0]->ResetPosition();
		player[1]->ResetPosition();

		pressedPlay = false;
	}


	if (showMenu)
	{
		screen->Clear(0);
		menuUI->Draw(screen);
		arrow->Draw(screen);

		audio->Play(audio->musicMenu);
	}

	if (showGameMode)
	{
		screen->Clear(0);
		gameModeUI->Draw(screen);
		arrow->Draw(screen);
	}

	if (showGame)
	{
		audio->Stop(audio->musicMenu);
		audio->Stop(audio->musicGameOver);
		player[0]->DyingAnimation(deltaTime);
		player[1]->DyingAnimation(deltaTime);
		for (int i = 0; i < 9; i++)
		{
			if (valcom[i])
			{
				valcom[i]->DyingAnimation(deltaTime);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (ONeal[i])
			{
				ONeal[i]->DyingAnimation(deltaTime);
			}
		}

		for (int i = 0; i < amountBricks * levels; i++)
		{
			if (bricks[i])
			{
				bricks[i]->playAnimation(deltaTime);
				if (bricks[i]->deleteObject)
				{
					DeleteBrick(i);
				}
			}
		}


		if (gameMode == 2)
		{
			//cout << currentLevel << endl;
			//screen1->Clear(0x000000);
			//screen2->Clear(0x000000);

			//valcom1->CheckBrickCollision();
			//ONeal1->CheckBrickCollision();


			map->camera2Player(0, static_cast<int>(player[0]->getX()));
			map->camera2Player(1, static_cast<int>(player[1]->getX()));

			map->RenderMap(screen1, 0); //add the first camera here
			map->RenderMap(screen2, 1); //add the second camera here

			if (extraFlameRange && extraFlameRange->MarkForDeletion())
			{
				delete extraFlameRange;
				extraFlameRange = nullptr;
			}

			if (extraBomb && extraBomb->MarkForDeletion())
			{
				delete extraBomb;
				extraBomb = nullptr;
			}

			//map.CheckCollision();
			door->Draw(screen1, 0);
			door->Draw(screen2, 1);
			player[0]->Draw(screen1, map->getCamera(0));
			player[0]->Draw(screen2, map->getCamera(1));
			player[1]->Draw(screen1, map->getCamera(0));
			player[1]->Draw(screen2, map->getCamera(1));

			bomb[0]->Draw(screen1, 0, deltaTime);
			bomb[0]->Draw(screen2, 1, 0);
			bomb[1]->Draw(screen1, 0, 0);
			bomb[1]->Draw(screen2, 1, deltaTime);

			//cout << "Player[1] dyingFrameCountdown: " << player[1]->dyingFrame << endl;

			if (!player[0]->dying)
			{
				player[0]->Move(deltaTime);
			}
			else
			{
				audio->Play(audio->gameOverSound);
			}
			if (!player[1]->dying)
			{
				player[1]->Move(deltaTime);
			}
			else
			{
				audio->Play(audio->gameOverSound);
			}


			switch (currentLevel)
			{
			case 0: Level0(deltaTime); break;
			case 1: Level1(deltaTime); break;
			default: break;
			}

			screen1->CopyTo(screen, 0, 0);
			screen2->CopyTo(screen, SCRWIDTH / 2, 0);
			//screen->CopyTo(screen, 640, 0);
		}

		if (gameMode == 1)
		{
			//cout << currentLevel << endl;
			//screen1->Clear(0x000000);
			//screen2->Clear(0x000000);


			//valcom1->CheckBrickCollision();
			//ONeal1->CheckBrickCollision();

			map->camera1Player(static_cast<int>(player[0]->getX()));

			map->RenderMap(screen, 2); //add the first camera here


			if (extraFlameRange && extraFlameRange->MarkForDeletion())
			{
				delete extraFlameRange;
				extraFlameRange = nullptr;
			}

			if (extraBomb && extraBomb->MarkForDeletion())
			{
				delete extraBomb;
				extraBomb = nullptr;
			}


			//map.CheckCollision();
			door->Draw(screen, 2);
			player[0]->Draw(screen, map->getCamera(2));

			if (!player[0]->dying)
			{
				player[0]->Move(deltaTime);
			}
			else
			{
				audio->Play(audio->gameOverSound);
			}

			bomb[0]->Draw(screen, 2, deltaTime);

			switch (currentLevel)
			{
			case 0: Level0(deltaTime); break;
			case 1: Level1(deltaTime); break;
			default: break;
			}

			if (player[0]->LEVEL_UP)
			{
				currentLevel = 1;
			}

			char pointsmsg[256];
			snprintf(pointsmsg, 256, "score: %i", score);
			screen->PrintScaled(pointsmsg, 1050, 23, 3, 3, 0x000000);

			//screen->CopyTo(screen, 640, 0);
		}
	}

	if (showControls)
	{
		//screen->Clear(0);
		controlsUI->Draw(screen);
		arrow->Draw(screen);
	}

	if (showGameOver)
	{
		screen->Clear(0);
		gameOverUI->Draw(screen);
		arrow->Draw(screen);
		audio->Stop(audio->musicLvl1);
		audio->Stop(audio->musicLvl2);
		audio->Play(audio->musicGameOver);
		audio->Stop(audio->gameOverSound);
	}
}

void Game::KeyUp(int const key)
{
	player[0]->KeyUpWASD(key);
	player[1]->KeyUpARROWS(key);
}

void Game::KeyDown(int const key)
{
	if (showGame)
	{
		player[0]->KeyDownWASD(key);
		player[1]->KeyDownARROWS(key);
	}
	if (showMenu || showGameOver || showControls || showGameMode)
	{
		arrow->keyDown(key);
	}
}