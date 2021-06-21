#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>
#include "texture.h"
#include <sol.hpp>
#include "entity.h"

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
    int numLayers;
    std::vector<std::map<int, Trigger>> triggers;
    int* entityPositions;

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
void LoadEntitiesPositionsOnMap(Map* map, std::vector<Entity> entities);
void SetOccupiedTile(Map* map, int x, int y);
void UnSetOccupiedTile(Map* map, int x, int y);
void PointToTile(Map map, int left, int top, int x, int y, int& tileX, int& tileY);
void LoadMap(Map* map, const char* luaFilePath, const char* textureFilePath);
void DrawMap(uint32_t* buffer, Map* map, int layer);
int GetTile(Map* map, int x, int y, int layer);
Trigger GetTrigger(Map* map, int x, int y, int layer);
bool IsBlocked(Map* map, int x, int y, int layer);
int CoordToIndex(Map* map, int x, int y);
void ClearMapTriggers(Map* map);

#endif
