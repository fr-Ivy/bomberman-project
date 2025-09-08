#pragma once

class map
{
public:
    void RenderMap(Surface* screen, Surface* TileSheet);
private:
    const int TILE_SIZE = 64;
    const int MAP_ROWS = 11;
    const int MAP_COLUMNS = 31; // 31
    const int MAP_WIDTH = 896;

};

