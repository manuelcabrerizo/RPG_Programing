#include "engine.h"

void UpdateColorBuffer(Engine* engine)
{
    SDL_UpdateTexture(engine->textureBuffer,
                      0,
                      (const void*)engine->colorBuffer,
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



