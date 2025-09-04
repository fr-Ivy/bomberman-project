#pragma once

class map
{
public:
    void RenderMap(Surface* screen, Surface* TileSheet);
private:
    int TILE_SIZE = 16;
    int MAP_ROWS = 11;
    int MAP_COLUMNS = 31;
};

//tell code how big the map is
//tell code how many tiles there are (how many rows and how many columns)
// calculate how big the tiles are
//go over each tile
//get the right tile from ID
//
