#pragma once

class bomb;

class Map
{
public:
    Map();
    ~Map();
    void RenderMap(Surface* screen, int cameraX);
    bool CheckCollision(int camera, int tx, int ty) const;
    bool checkPixelCollision(const bool* playerPixelVisible, int tx, int ty, int SPRITE_SIZE) const;
    void camera(int camera, int x);
    int Min(int number1, int number2);
    int Max(int number1, int number2);

    int GetWidth() { return MAP_WIDTH; }

    float getCamera(int camera) const { return static_cast<float>(cameraX[camera]); }

    static constexpr int TILE_SIZE = 64;

private:
    Surface* tileSheet = nullptr;

    static constexpr int MAP_ROWS = 11;
    static constexpr int MAP_COLUMNS = 31;
    static constexpr int MAP_WIDTH = 896;
    int tiles[MAP_ROWS][MAP_COLUMNS];
    int cameraX[2] = {0,0}; // cameraX[0] for screen1, cameraX[1] for screen2
};

