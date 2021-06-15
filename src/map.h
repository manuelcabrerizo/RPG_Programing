#ifndef MAP_H
#define MAP_H

#include "texture.h"

struct Map
{
    int x;
    int y;
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    int* data;
    Texture image;
    float* uvs;

    int camX;
    int camY;

    int topTile;
    int leftTile;
    int bottomTile;
    int rightTile;
};

Map LoadLuaMap(const char* filePath);
void PointToTile(Map map, int left, int top, int x, int y, int& tileX, int& tileY);
void LoadMap(Map* map, const char* luaFilePath, const char* textureFilePath);
void DrawMap(uint32_t* buffer, Map* map);

#endif
