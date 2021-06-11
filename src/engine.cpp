#include "engine.h"

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
            uint8_t red = color >> 16;
            uint8_t green = color >> 8;
            uint8_t blue = color;
            color = alpha << 24 | blue << 16 | green << 8 | red;
            DrawPixel(buffer, actual_x, actual_y, color);
            j++;
        }
        i++;
    }
}

