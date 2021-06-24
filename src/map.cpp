#include "map.h"
#include "engine.h"

#include <string.h>

Map LoadLuaMap(const char* filePath)
{
    Map map = {}; 
    //sol::state lua;
    map.lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    map.lua.script_file(filePath); 
    sol::table map_t = map.lua["map"];
    sol::optional<sol::table> exist_map = map.lua["map"];
    if(exist_map == sol::nullopt)
    {
        printf("ERROR::LUA::FILE::NOT::FOUND\n");
    }
    else
    { 
        map.width = (int)map_t["width"];
        map.height = (int)map_t["height"];
        map.tileWidth = (int)map_t["tilewidth"];
        map.tileHeight = (int)map_t["tileheight"];  

        sol::table tilesets = map_t["tilesets"];
        int index = 0;
        while(true)
        {
            sol::optional<sol::table> exist_tilesets = tilesets[index];
            if(exist_tilesets == sol::nullopt)
            {
                break;
            }
            else
            {
                std::string tilesetName = tilesets[index]["name"];
                if(strcmp(tilesetName.c_str(), "collision_graphic") == 0)
                {
                    map.blockingTile = (int)tilesets[index]["firstgid"];
                } 
            }
            index++;
        }
        sol::table layers = map_t["layers"];
        int indexLayer = 0;
        while(true)
        {
            sol::optional<sol::table> exist_layer = layers[indexLayer];
            if(exist_layer == sol::nullopt)
            {
                break;
            }
            indexLayer++;
        }
        map.numLayers = indexLayer / 3;  
    }
    return map; 
}

void LoadEntitiesPositionsOnMap(Map* map, Entity* entities, int numberOfEntities)
{
    for(int y = 0; y < map->height; y++)
    {
        for(int x = 0; x < map->width; x++)
        {
            ArrayPush(map->entityPositions, 0, int);
        }
    }

    for(int i = 0; i < numberOfEntities; i++)
    {
        map->entityPositions[CoordToIndex(map, entities[i].tileX, entities[i].tileY)] = map->blockingTile;
    }
}

void SetOccupiedTile(Map* map, int x, int y)
{
    map->entityPositions[CoordToIndex(map, x, y)] = map->blockingTile;
}

void UnSetOccupiedTile(Map* map, int x, int y)
{
    map->entityPositions[CoordToIndex(map, x, y)] = 0;
}

int GetTileEntity(Map* map, int x, int y)
{
    return map->entityPositions[CoordToIndex(map, x, y)];
}

int GetTile(Map* map, int x, int y, int layer)
{
    sol::table data = map->lua["map"]["layers"][layer]["data"];
    return (int)data[CoordToIndex(map, x, y) + 1] - 1;
}

Trigger GetTrigger(Map* map, int x, int y, int layer)
{
    Trigger trigger = map->triggers[layer][CoordToIndex(map, x, y)];
    return trigger;
}

int CoordToIndex(Map* map, int x, int y)
{
    return x + y * map->width;
}

bool IsBlocked(Map* map, int x, int y, int layer)
{
    int tile = GetTile(map, x, y, layer + 2) + 1;
    int tileEntity = GetTileEntity(map, x, y);
    return tile == map->blockingTile || tileEntity == map->blockingTile;
}

void PointToTile(Map* map, int x, int y, int& tileX, int& tileY)
{
    x = IntMax(map->x, x);
    y = IntMax(map->y, y);
    
    x = IntMin(map->x + (map->width * map->tileWidth), x);
    y = IntMin(map->y + (map->height * map->tileHeight), y);

    tileX = ((x - map->x) / map->tileWidth);
    tileY = ((y - map->y) / map->tileHeight);
}


void LoadMap(Map* map, const char* luaFilePath, const char* textureFilePath)
{
    *map = LoadLuaMap(luaFilePath);
    map->image = LoadTexture(textureFilePath);
    map->uvs = GenerateUVs(map->image,
                           map->tileWidth,
                           map->tileHeight);
}

void DrawMap(uint32_t* buffer, Map* map, int layer)
{
    int layerIndex = layer * 3;

    PointToTile(map,
                0, 
                0, 
                map->leftTile,
                map->topTile);

    PointToTile(map, 
                WNDWIDTH + map->tileWidth,
                WNDHEIGHT + map->tileHeight,
                map->rightTile,
                map->bottomTile);

    for(int y = map->topTile; y < map->bottomTile; y++)
    {
        for(int x = map->leftTile; x < map->rightTile; x++)
        {
            DrawFrame(buffer,
                      map->uvs,
                      map->x + x * map->tileWidth,
                      map->y + y * map->tileHeight,
                      GetTile(map, x, y, layerIndex),
                      &map->image);
           DrawFrame(buffer,
                      map->uvs,
                      map->x + x * map->tileWidth,
                      map->y + y * map->tileHeight,
                      GetTile(map, x, y, layerIndex + 1),
                      &map->image);
        }
    }
}


void ClearMapTriggers(Map* map)
{
    for(int i = 0; i < map->triggers.size(); i++)
    {
        map->triggers[i].clear();
    }
    map->triggers.clear();
}   
