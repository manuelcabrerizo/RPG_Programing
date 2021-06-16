#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <sol.hpp>
#include "darray.h"
#include "map.h"
#include "entity.h"
#include "input.h"

#define WNDWIDTH 640
#define WNDHEIGHT 480

// this is the main struct for the enigne
// here we r going to declear all the variables 
// that we need to have in all are engine... 
struct Engine
{
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* textureBuffer;
    uint32_t* colorBuffer;
    Input input;
    
    Map map;
    Entity hero;

    StateMachineFP sm;
};

int IntMax(int a, int b);
int IntMin(int a, int b);

void RenderColorBuffer(Engine* engine);
void ClearBuffer(uint32_t* buffer, uint32_t color);
void DrawPixel(uint32_t* buffer, int x, int y, uint32_t color);
void DrawRect(uint32_t* buffer, int x, int y, int width, int height, uint32_t color);
void DrawTexture(uint32_t* buffer, int x, int y, int width, int height, uint32_t* pixels);
float* GenerateUVs(Texture texture, int tileWidth, int tileHeight);
void DrawFrame(uint32_t* buffer, float* uvs, int x, int y, int frame, Texture* texture);

#endif
