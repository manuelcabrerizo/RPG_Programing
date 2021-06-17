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
  
    }
    return map; 
}

int GetTile(Map* map, int x, int y, int layer)
{
    sol::table data = map->lua["map"]["layers"][layer]["data"];
    return (int)data[(x + y * map->width) + 1] - 1;
}

bool IsBlocked(Map* map, int x, int y, int layer)
{
    int tile = GetTile(map, x, y, layer + 1) + 1;
    return tile == map->blockingTile;
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

void DrawMap(uint32_t* buffer, Map* map)
{
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
                      GetTile(map, x, y, 0),
                      &map->image);
        }
    }
}



/*
Map LoadLuaMap(const char* filePath)
{
    Map map = {}; 
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    lua.script_file(filePath);

    sol::table map_t = lua["map"];
    sol::optional<sol::table> exist_map = lua["map"];
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

        sol::table layer = map_t["layers"];
        map.layers = map_t["layers"];
        sol::optional<sol::table> exist_layer = map_t["layers"];
        if(exist_layer == sol::nullopt)
        {
            printf("ERROR::LAYERS::NOT::FOUND\n");
        }
        else
        {
            int layerIndex = 0;
            while(true)
            {
                sol::optional<sol::table> exist_index_layer = layer[layerIndex];
                if(exist_index_layer == sol::nullopt)
                {
                    break;
                }
                else
                {
                    std::string layerName = layer[layerIndex]["name"];
                    if(strcmp(layerName.c_str(), "base") == 0)
                    {
                        sol::table data = layer[layerIndex]["data"]; 
                        for(int i = 0; i < (map.width * map.height); i++)
                        {
                            ArrayPush(map.data, (int)data[i + 1] - 1, int); 
                        }
                    }
                    else if(strcmp(layerName.c_str(), "collition") == 0)
                    {
                    
                    }
                }
                layerIndex++;
            } 
        }        
    }
    return map; 
}
*/
