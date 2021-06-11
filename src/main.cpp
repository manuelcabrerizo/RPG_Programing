#include <stdio.h>
#include <stdlib.h> 

#include "engine.h"

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

void UpdateAndRender(Engine* engine)
{
    // update stuff 
 
    // render stuff
    ClearBuffer(engine->colorBuffer, 0xFF00FF00);
    
    DrawPixel(engine->colorBuffer, 5, 5, 0xFF0000FF);
    DrawRect(engine->colorBuffer, -25, 10, 50, 25, 0xFFFF0000);

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

    engine.isRunning = true;
    while(engine.isRunning)
    {
        HandleEvents(&engine);
        UpdateAndRender(&engine);
    }

    free(engine.colorBuffer);
    SDL_DestroyRenderer(engine.renderer);
    SDL_DestroyWindow(engine.window);
    SDL_Quit();

    return 0;
}
