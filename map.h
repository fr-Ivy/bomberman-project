#pragma once

class Map
{
public:
    Map();
    void RenderMap(Surface* screen, Surface* TileSheet);
    bool CheckCollision(int tx, int ty) const;

    static constexpr int TILE_SIZE = 64;

private:
    static constexpr int MAP_ROWS = 11;
    static constexpr int MAP_COLUMNS = 31;
    static constexpr int MAP_WIDTH = 896;
    int tiles[MAP_ROWS][MAP_COLUMNS];
};

