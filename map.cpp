#include "precomp.h"
#include "Map.h"
#include <iostream>


Map::Map()
{
	const char layout[MAP_ROWS][MAP_COLUMNS] =
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

void Map::RenderMap(Surface* screen, Surface* TileSheet)
{
	for (int y = 0; y < MAP_ROWS; y++)
	{
		for (int x = 0; x < MAP_COLUMNS; x++)
		{
			int tileX = TILE_SIZE * x - cameraX; //start point at 0
			int tileY = TILE_SIZE * y; //start point at 0
			if (tileX + TILE_SIZE >= 0 && tileY + TILE_SIZE >= 0 && tileX <= SCRWIDTH && tileY <= SCRHEIGHT) //is the tile currently in-screen
			{
				const int minOffScreenX = max(0, tileX); //look for the highest number between these
				const int minOffScreenY = max(0, tileY);
				const int maxOffScreenX = min(SCRWIDTH, tileX + TILE_SIZE); //look for the lowest number between these
				const int maxOffScreenY = min(SCRHEIGHT, tileY + TILE_SIZE);

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

				uint* dst = screen->pixels + tileX + tileY * SCRWIDTH;
				uint* src = TileSheet->pixels + currentColumn + currentRow * MAP_WIDTH;

				const uint width = TILE_SIZE - minOffScreen.x - maxOffScreen.x;
				const uint height = TILE_SIZE - minOffScreen.y - maxOffScreen.y;

				for (int i = 0; i < height; i++, src += MAP_WIDTH, dst += SCRWIDTH)
				{
					for (int j = 0; j < width; j++)
					{
						dst[j] = src[j];
					}
				}
			}
		}
	}
}

void Map::camera(int x)
{
	cameraX = x - TILE_SIZE;
}

bool Map::CheckCollision(int tx, int ty) const
{
	int x = (tx + cameraX) / TILE_SIZE;
	int y = ty / TILE_SIZE;

	//if (x < 0 || x >= MAP_COLUMNS || y < 0 || y >= MAP_ROWS)
		//return false;

	const int ID = tiles[y][x];
	//cout << ID << endl;
	return ID == 46;
}

bool Map::checkPixelCollision(const bool* playerPixelVisible, int tx, int ty, int SPRITE_SIZE) const
{
	bool tilePixelVisible[TILE_SIZE * TILE_SIZE];
	for (int i = 0; i < TILE_SIZE * TILE_SIZE; i++) {
		tilePixelVisible[i] = true;
	}

	int x = (tx) / TILE_SIZE;
	int y = ty / TILE_SIZE;

	const int ID = tiles[y][x];

	int playerLeft, playerRight, playerTop, playerBottom;
	int tileLeft, tileRight, tileTop, tileBottom;
	int left, right, top, bottom;
	int columns, rows;

	playerLeft = tx;
	playerRight = tx + SPRITE_SIZE - 1;
	playerTop = ty;
	playerBottom = ty + SPRITE_SIZE - 1;

	tileLeft = x * TILE_SIZE;
	tileRight = x * TILE_SIZE + TILE_SIZE - 1;
	tileTop = y * TILE_SIZE;
	tileBottom = y * TILE_SIZE + TILE_SIZE - 1;


	left = max(playerLeft, tileLeft);
	right = min(playerRight, tileRight);
	top = max(playerTop, tileTop);
	bottom = min(playerBottom, tileBottom);
	columns = right - left + 1;
	rows = bottom - top + 1;

	playerLeft = left - playerLeft;
	playerTop = top - playerTop;

	tileLeft = left - tileLeft;
	tileTop = top - tileTop;

	cout << "tx, ty: " << tx << ", " << ty << endl;
	cout << "tile x, y: " << x << ", " << y << endl;
	cout << "player offsets: " << playerLeft << ", " << playerTop << endl;
	cout << "columns, rows: " << columns << ", " << rows << endl;
	cout << "ID: " << ID << endl;


	//cout << ID << endl;
	if (ID == 46)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (playerPixelVisible[(playerLeft + j) + (playerTop + i) * SPRITE_SIZE] &&
					tilePixelVisible[(tileLeft + j) + (tileTop + i) * TILE_SIZE])
				{
					return true;
				}
			}
		}
	}
	return false;
}