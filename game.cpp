// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "Map.h"
#include "Player.h"


Surface* TileSheet = nullptr;;
Map map;
Player player;

Sprite playerSprite(new Surface("assets/player/playerSprites.png"), 19);

void Game::Init()
{
    TileSheet = new Surface("assets/tiled/TileSet.png");
	player = Player(&playerSprite, screen);
}


void Game::Tick( float deltaTime )
{
	screen->Clear(0x000000);
	map.RenderMap(screen, TileSheet);
	player.move(deltaTime, map);
	player.Draw();
	//map.CheckCollision();
	player.Pixel();
}