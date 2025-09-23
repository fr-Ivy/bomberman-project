#pragma once

class bomb;

class Map
{
public:
    Map();
    ~Map();
    void RenderMap(Surface* screen);
    bool CheckCollision(int tx, int ty) const;
    bool checkPixelCollision(const bool* playerPixelVisible, int tx, int ty, int SPRITE_SIZE) const;
    void camera(int x);

    int getCamera() { return cameraX; }

    static constexpr int TILE_SIZE = 64;

private:
    Surface* tileSheet = nullptr;

    static constexpr int MAP_ROWS = 11;
    static constexpr int MAP_COLUMNS = 31;
    static constexpr int MAP_WIDTH = 896;
    int cameraX = 0;
    int tiles[MAP_ROWS][MAP_COLUMNS];
};

