// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "map.h"


Surface* TileSheet = nullptr;
map Map;

void Game::Init()
{

    TileSheet = new Surface("assets/tiled/TileSet.png");
}


void Game::Tick( float /* deltaTime */ )
{
	screen->Clear(0x000000);
	Map.RenderMap(screen, TileSheet);
}