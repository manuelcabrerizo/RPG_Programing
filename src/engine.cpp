
#include <math.h>
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

Texture LoadTexture(const char* filePath)
{
    Texture texture;
    SDL_Surface* tempSurface = SDL_LoadBMP(filePath);
    texture.pixels = (uint32_t*)tempSurface->pixels;
    texture.width = tempSurface->w;
    texture.height = tempSurface->h;
    return texture;
}

void RenderColorBuffer(Engine* engine)
{
    SDL_UpdateTexture(engine->textureBuffer,
                      0,
                      engine->colorBuffer,
                      (int)WNDWIDTH * sizeof(uint32_t));
    SDL_RenderCopy(engine->renderer, engine->textureBuffer, 0, 0);
    SDL_RenderPresent(engine->renderer);
}

void ClearBuffer(uint32_t* buffer, uint32_t color)
{
    for(int i = 0; i < (int)WNDWIDTH*(int)WNDHEIGHT; i++)
    {
        buffer[i] = color;
    }
}

void DrawPixel(uint32_t* buffer, int x, int y, uint32_t color)
{
    if(x >= 0 && y >= 0 && x <= (int)WNDWIDTH && y <= (int)WNDHEIGHT)
    {
        buffer[x + (y * (int)WNDWIDTH)] = color;
    }
}

void DrawRect(uint32_t* buffer, int x, int y, int width, int height, uint32_t color)
{
    for(int actual_y = y; actual_y < y + height; actual_y++)
    {
        for(int actual_x = x; actual_x < x + width; actual_x++)
        {
            DrawPixel(buffer, actual_x, actual_y, color);
        }
    }
}

void DrawTexture(uint32_t* buffer, int x, int y, int width, int height, uint32_t* pixels)
{
    int i = 0;
    for(int actual_y = y; actual_y < y + height; actual_y++)
    {
        int j = 0;
        for(int actual_x = x; actual_x < x + width; actual_x++)
        {
            uint32_t color = pixels[j + (i * width)];
            uint8_t alpha = color >> 24;
            uint8_t red   = color >> 16;
            uint8_t green = color >> 8;
            uint8_t blue  = color;
            color = alpha << 24 | blue << 16 | green << 8 | red;
            if(alpha > 128)
            {
                DrawPixel(buffer, actual_x, actual_y, color);
            }
            j++;
        }
        i++;
    }
}

void DrawFrame(uint32_t* buffer, float* uvs, int x, int y, int frame, Texture* texture)
{
    float* actualUVs = uvs + (frame * 4);
    int xPos    = (int)(round(actualUVs[0] * (float)texture->width)); 
    int yPos    = (int)(round(actualUVs[1] * (float)texture->height));
    int xWidth  = (int)(round(actualUVs[2] * (float)texture->width)); 
    int yHeight = (int)(round(actualUVs[3] * (float)texture->height));
    
    int i = 0;
    for(int actual_y = yPos; actual_y < yHeight; actual_y++)
    { 
        int j = 0;
        for(int actual_x = xPos; actual_x < xWidth; actual_x++)
        {
            uint32_t color = texture->pixels[actual_x + (actual_y * texture->width)];
            uint8_t alpha = color >> 24;
            uint8_t red   = color >> 16;
            uint8_t green = color >> 8;
            uint8_t blue  = color;
            color = alpha << 24 | blue << 16 | green << 8 | red;
            if(alpha > 128)
            {
                DrawPixel(buffer, x + j, y + i, color);
            }
            j++;
        }
        i++;
    }
}

float* GenerateUVs(Texture texture, int tileWidth, int tileHeight)
{
    float* uvs = NULL;

    float width = (float)tileWidth / (float)texture.width;
    float height = (float)tileHeight / (float)texture.height;
    int cols = texture.width / tileWidth;
    int rows = texture.height / tileHeight;

    float u0 = 0.0f;
    float v0 = 0.0f;
    float u1 = width;
    float v1 = height;

    for(int y = 0; y < rows; y++)
    {
        for(int x = 0; x < cols; x++)
        {
            ArrayPush(uvs, u0, float);
            ArrayPush(uvs, v0, float);
            ArrayPush(uvs, u1, float);
            ArrayPush(uvs, v1, float);
            u0 += width;
            u1 += width;
        }
        u0 = 0;
        u1 = width;
        v0 += height;
        v1 += height;
    }
    return uvs;
}


