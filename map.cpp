#include "precomp.h"
#include "map.h"

const char tiles[11][31] =
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

void map::RenderMap(Surface* screen, Surface* TileSheet)
{
	for (int y = 0; y < MAP_ROWS; y++)
	{
		for (int x = 0; x < MAP_COLUMNS; x++)
		{
			int tileX = TILE_SIZE * y;
			int tileY = TILE_SIZE * x;
			if (tileX + TILE_SIZE >= 0 && tileY + TILE_SIZE >= 0 && tileX <= SCRWIDTH && tileY <= SCRHEIGHT) //is the tile currently in-screen
			{
				const int minOffScreenX = max(0, tileX);
				const int minOffScreenY = max(0, tileY);
				const int maxOffScreenX = min(SCRWIDTH, tileX + TILE_SIZE);
				const int maxOffScreenY = min(SCRHEIGHT, tileY + TILE_SIZE);

				const uint2 minOffScreen = { (minOffScreenX - tileX), (minOffScreenY - tileY) };
				const uint2 maxOffScreen = { (maxOffScreenX - tileX - TILE_SIZE), (maxOffScreenY - tileY - TILE_SIZE) };

				const int ID = tiles[y][x] - 1; //gets the ID
				int currentColumn = (ID % (MAP_WIDTH / TILE_SIZE)) * TILE_SIZE;
				int currentRow = (ID / (MAP_WIDTH / TILE_SIZE)) * TILE_SIZE;

				tileX += minOffScreen.x;
				tileY += minOffScreen.y;
				currentColumn += minOffScreen.x;
				currentRow += minOffScreen.y;


				uint* dst = screen->pixels + tileY + tileX * SCRWIDTH;
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
