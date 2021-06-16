#include "map.h"
#include "engine.h"

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
                    sol::table data = layer[layerIndex]["data"]; 
                    for(int i = 0; i < (map.width * map.height); i++)
                    {
                        ArrayPush(map.data, (int)data[i + 1] - 1, int); 
                    }
                }
                layerIndex++;
            } 
        }        
    }
    return map; 
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
                      map->data[x + y * map->width],
                      &map->image);
        }
    }
}
