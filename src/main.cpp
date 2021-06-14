#include <stdio.h>
#include <stdlib.h> 

#include "engine.h"

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

void HandleEvents(Engine* engine)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        
            case SDL_QUIT:
            {
                engine->isRunning = false;
            }break;
            case SDL_KEYDOWN:
            {
                if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    engine->isRunning = false;
                }
            }break;
            default:
            {
            
            }break; 
        }
    }
}

int data[]
{
        1, 4, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
        12, 15, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 73, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 73, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        45, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66
};

void TempFunction()
{
    for(int i = 0; i < 12*12; i++)
    {
        data[i] = data[i] - 1;
    }
}

int GetTile(int x, int y, int map[])
{
    return map[x + y * 20];
}

void UpdateAndRender(Engine* engine, float dt)
{
    // update stuff 
 
    // render stuff
    ClearBuffer(engine->colorBuffer, 0xFF000000);

    for(int y = 0; y < 12; y++)
    {
        for(int x = 0; x < 12; x++)
        {
            DrawFrame(engine->colorBuffer,
              engine->uvs,
              x * 16,
              y * 16,
              data[x + (y * 12)],
              &engine->image);
        }
    }

    RenderColorBuffer(engine);
}

int main(int argc, char* argv[])
{
    Engine engine = {};
    printf("Initializing SDL\n");
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("ERROR :: Initializing SDL\n");
        return 1;
    }
    engine.window = SDL_CreateWindow("RPG", 
                                     SDL_WINDOWPOS_CENTERED, 
                                     SDL_WINDOWPOS_CENTERED, 
                                     WNDWIDTH, WNDHEIGHT, 
                                     SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);
    if(engine.window != 0)
    {
        engine.renderer = SDL_CreateRenderer(engine.window, -1, 0);
        if(engine.renderer == 0)
        {
            printf("ERROR :: Creating the RENDERER\n");
            return 1;
        }
    }
    else
    {
        printf("ERROR :: Creating the WINDOW\n");
        return 1;
    }

    engine.colorBuffer = (uint32_t*)malloc(((int)WNDWIDTH * (int)WNDHEIGHT) * sizeof(uint32_t));
    engine.textureBuffer = SDL_CreateTexture(engine.renderer,
                                             SDL_PIXELFORMAT_RGBA32, 
                                             SDL_TEXTUREACCESS_STREAMING,
                                             (int)WNDWIDTH,
                                             (int)WNDHEIGHT);

    engine.image = LoadTexture("./assets/rpg_indoor.bmp");
    engine.uvs = GenerateUVs(engine.image, 16, 16);

    TempFunction();



    engine.isRunning = true;

    uint32_t previusFrameTime = 0;
    while(engine.isRunning)
    {
        int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previusFrameTime);
        if(timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
        {
            SDL_Delay(timeToWait);
        }
        uint32_t currentFrameTime = SDL_GetTicks();
        float dt = (float)(currentFrameTime - previusFrameTime) / 1000.0f; 

        HandleEvents(&engine);
        UpdateAndRender(&engine, dt);  
        previusFrameTime = currentFrameTime;
    }

    free(engine.colorBuffer);
    SDL_DestroyRenderer(engine.renderer);
    SDL_DestroyWindow(engine.window);
    SDL_Quit();

    return 0;
}
