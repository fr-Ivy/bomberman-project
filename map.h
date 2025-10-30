#pragma once
#include "game.h"

class Map
{
public:
    Map(Game* game);
    ~Map();
    void RenderMap(Surface* screen, int camera);
    bool CheckCollision(int tx, int ty) const;
    bool checkPixelCollision(Player* player, int tx, int ty, int SPRITE_SIZE) const;
    void camera1Player(int x);
    void camera2Player(int camera, int x);
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
    int cameraX[3] = {0, 0, 0}; // cameraX[0] for screen1, cameraX[1] for screen2, cameraX[2] for single-player

    Game* game = nullptr;
};

