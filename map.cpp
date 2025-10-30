#include "precomp.h"
#include "Map.h"
#include "game.h"
#include "player.h"
#include <iostream>


Map::Map(Game* game) : game(game)
{
	tileSheet = new Surface("assets/tiled/TileSet.png");

	const int layout[MAP_ROWS][MAP_COLUMNS] =
	{
		{46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46},
		{46,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,46},
		{46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46},
		{46,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,46},
		{46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46},
		{46,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,46},
		{46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46},
		{46,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,46},
		{46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46,57,46},
		{46,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,46},
		{46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46}
	};

	for (int y = 0; y < MAP_ROWS; y++) {
		for (int x = 0; x < MAP_COLUMNS; x++) {
			tiles[y][x] = layout[y][x];
		}
	}
}

Map::~Map()
{
	delete tileSheet;
}


/*const char tiles[11][11] =
{
	{46,46,46,46,46,46,46,46,46,46,46},
	{46,57,57,57,57,57,57,57,57,57,46},
	{46,57,46,57,46,57,46,57,46,57,46},
	{46,57,57,57,57,57,57,57,57,57,46},
	{46,57,46,57,46,57,46,57,46,57,46},
	{46,57,57,57,57,57,57,57,57,57,46},
	{46,57,46,57,46,57,46,57,46,57,46},
	{46,57,57,57,57,57,57,57,57,57,46},
	{46,57,46,57,46,57,46,57,46,57,46},
	{46,57,57,57,57,57,57,57,57,57,46},
	{46,46,46,46,46,46,46,46,46,46,46}
};
*/

void Map::RenderMap(Surface* screen, int const camera)
{
	int screenWidth = screen->width;
	int screenHeight = screen->height;
	int camera_X = cameraX[camera];

	for (int y = 0; y < MAP_ROWS; y++)
	{
		for (int x = 0; x < MAP_COLUMNS; x++)
		{
			int tileX = TILE_SIZE * x - camera_X; //start point at 0
			int tileY = TILE_SIZE * y; //start point at 0
			if (tileX + TILE_SIZE >= 0 && tileY + TILE_SIZE >= 0 && tileX <= screenWidth && tileY <= screenHeight) //is the tile currently in-screen
			{
				const int minOffScreenX = Max(0, tileX); //look for the highest number between these
				const int minOffScreenY = Max(0, tileY);
				const int maxOffScreenX = Min(screenWidth, tileX + TILE_SIZE); //look for the lowest number between these
				const int maxOffScreenY = Min(screenHeight, tileY + TILE_SIZE);

				const uint2 minOffScreen = { abs(minOffScreenX - tileX), abs(minOffScreenY - tileY) }; //make the minOffScreen positive
				const uint2 maxOffScreen = { abs(maxOffScreenX - tileX - TILE_SIZE), abs(maxOffScreenY - tileY - TILE_SIZE) }; //make the maxOffScreen positive

				const int ID = tiles[y][x] - 1; //gets the ID
				int currentColumn = (ID % (MAP_WIDTH / TILE_SIZE)) * TILE_SIZE;
				int currentRow = (ID / (MAP_WIDTH / TILE_SIZE)) * TILE_SIZE;

				//what part needs to be visible
				tileX += minOffScreen.x; 
				tileY += minOffScreen.y;
				currentColumn += minOffScreen.x;
				currentRow += minOffScreen.y;

				uint* dst = screen->pixels + tileX + tileY * screenWidth;
				uint* src = tileSheet->pixels + currentColumn + currentRow * MAP_WIDTH;

				const uint width = TILE_SIZE - minOffScreen.x - maxOffScreen.x;
				const uint height = TILE_SIZE - minOffScreen.y - maxOffScreen.y;

				for (uint i = 0; i < height; i++, src += MAP_WIDTH, dst += screenWidth)
				{
					for (uint j = 0; j < width; j++)
					{
						dst[j] = src[j];
					}
				}
			}
		}
	}
}

void Map::camera1Player(int x)
{
	//cout << x << endl;
	int center = SCRWIDTH / 2;
	int maxCameraX = MAP_COLUMNS * TILE_SIZE - SCRWIDTH;

	cameraX[2] = Max(0, Min(x - center, maxCameraX));
}

void Map::camera2Player(int const camera, int const x)
{
	//cout << x << endl;
	int center = SCRWIDTH / 4;
	int maxCameraX = MAP_COLUMNS * TILE_SIZE - SCRWIDTH / 2;

	cameraX[camera] = Max(0, Min(x - center, maxCameraX));

	//cout << cameraX[0] << endl;
}

bool Map::CheckCollision(int const tx, int const ty) const
{
	int x = tx / TILE_SIZE;
	int y = ty / TILE_SIZE;

	if (x < 0 || x >= MAP_COLUMNS || y < 0 || y >= MAP_ROWS)
		return false;

	const int ID = tiles[y][x];
	//cout << ID << endl;
	return ID == 46;
}



bool Map::checkPixelCollision(Player* player, int const tx, int const ty, int const SPRITE_SIZE) const
{
	game->screen1->Plot(10, 10, 0xff00ff); // felroze testpixel
	//std::cout << "checkPixelCollision called at tx=" << tx << ", ty=" << ty << std::endl;
	int x = tx / TILE_SIZE;
	int y = ty / TILE_SIZE;

	const int ID = tiles[y][x];
	//std::cout << "Tile ID: " << ID << std::endl;

	bool tilePixelVisible[TILE_SIZE * TILE_SIZE];
	for (int i = 0; i < TILE_SIZE * TILE_SIZE; i++) 
	{
		tilePixelVisible[i] = true;
	}


	int playerLeft = tx;
	int const playerRight = tx + SPRITE_SIZE;
	int playerTop = ty;
	int const playerBottom = ty + SPRITE_SIZE;

	int tileLeft = x * TILE_SIZE;
	int const tileRight = x * TILE_SIZE + TILE_SIZE;
	int tileTop = y * TILE_SIZE;
	int const tileBottom = y * TILE_SIZE + TILE_SIZE;


	int const left = max(playerLeft, tileLeft);
	int const right = min(playerRight, tileRight);
	int const top = max(playerTop, tileTop);
	int const bottom = min(playerBottom, tileBottom);
	int const columns = right - left;
	int const rows = bottom - top;

	//std::cout << "columns=" << columns << ", rows=" << rows << std::endl;

	playerLeft = left - playerLeft;
	playerTop = top - playerTop;
	tileLeft = left - tileLeft;
	tileTop = top - tileTop;

	//cout << "tx, ty: " << tx << ", " << ty << endl;
	//cout << "tile x, y: " << x << ", " << y << endl;
	//cout << "player offsets: " << playerLeft << ", " << playerTop << endl;
	//cout << "columns, rows: " << columns << ", " << rows << endl;
	//cout << "ID: " << ID << endl;

	bool hit = false;
	//cout << ID << endl;
	if (ID == 46)
	{
		int tileScreenX = x * TILE_SIZE;
		int tileScreenY = y * TILE_SIZE;

		for (int i = 0; i < TILE_SIZE; i++)
		{
			for (int j = 0; j < TILE_SIZE; j++)
			{
				game->screen1->Plot(tileScreenX + j, tileScreenY + i, 0xff0000);
			}
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (player->pixelVisible[(playerLeft + j) + (playerTop + i) * SPRITE_SIZE] &&
					tilePixelVisible[(tileLeft + j) + (tileTop + i) * TILE_SIZE])
				{
					hit = true;
				}
			}
		}
	}
	return hit;
}


int Map::Min(int number1, int number2)
{
	return (number1 < number2) ? number1 : number2;
}

int Map::Max(int number1, int number2)
{
	return (number1 > number2) ? number1 : number2;
}