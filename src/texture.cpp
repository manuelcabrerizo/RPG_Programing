#include "texture.h"
#include <SDL2/SDL.h>

Texture LoadTexture(const char* filePath)
{
    Texture texture;
    SDL_Surface* tempSurface = SDL_LoadBMP(filePath);
    texture.pixels = (uint32_t*)tempSurface->pixels;
    texture.width = tempSurface->w;
    texture.height = tempSurface->h;
    return texture;
}
