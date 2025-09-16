// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "Map.h"
#include "Player.h"


void Game::Init()
{
    TileSheet = new Surface("assets/tiled/TileSet.png");
	playerSprite = new Sprite (new Surface("assets/player/playerSprites.png"), 19);
	player = new Player(playerSprite, screen);
	map = new Map(); //On the heap memory
	player->SetMapPtr(map);
}


void Game::Tick( float deltaTime )
{
	screen->Clear(0x000000);
	map->RenderMap(screen, TileSheet);
	player->move(deltaTime);
	player->Draw();
	//map.CheckCollision();
	player->Pixel();
}