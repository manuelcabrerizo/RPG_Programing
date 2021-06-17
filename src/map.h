#ifndef MAP_H
#define MAP_H

#include "texture.h"
#include <sol.hpp>

struct Map
{
    sol::state lua;
    int x;
    int y;
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    Texture image;
    float* uvs;

    int camX;
    int camY;

    int topTile;
    int leftTile;
    int bottomTile;
    int rightTile;

    // collition layer
    int blockingTile;
};

Map LoadLuaMap(const char* filePath);
void PointToTile(Map map, int left, int top, int x, int y, int& tileX, int& tileY);
void LoadMap(Map* map, const char* luaFilePath, const char* textureFilePath);
void DrawMap(uint32_t* buffer, Map* map);
int GetTile(Map* map, int x, int y, int layer);
bool IsBlocked(Map* map, int x, int y, int layer);

#endif
