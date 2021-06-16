#ifndef WAITSTATE_H
#define WAITSTATE_H

#include <stdio.h>
#include <cstdarg>

#include "stateMachine.h"
#include "map.h"
#include "entity.h"
#include "input.h"

void WaitStateOnEnter(va_list* valist, int num)
{
    va_list actual_Valist = *valist; 
    Entity* entity = NULL;
 
    for(int i = 0; i < num; i++)
    {
        if(i == 0)
        {
            entity = va_arg(actual_Valist, Entity*);
        }
    }

    entity->numFrames = 1; 
}

void WaitStateOnExit(va_list* valist, int num)
{
}

void WaitStateUpdate(va_list* valist, int num, float dt)
{    
    va_list actual_Valist = *valist; 
    Entity* entity = NULL;
    Map* map = NULL;
    Input* input = NULL;
    StateMachineFP* sm = NULL;

    for(int i = 0; i < num; i++)
    {
        if(i == 0)
        {
            entity = va_arg(actual_Valist, Entity*);
        }
        if(i == 1)
        {
            map = va_arg(actual_Valist, Map*);
        }
        if(i == 2)
        {
            input = va_arg(actual_Valist, Input*);
        }
        if(i == 3)
        {
            sm = va_arg(actual_Valist, StateMachineFP*);
        }
    }
    
    if(GetKeyDown(input, SDL_SCANCODE_A))
    {
        entity->xMove = -1;
        entity->yMove = 0;
        sm->ChangeState(entity->moveState, 4, (void*)entity,
                                              (void*)map,
                                              (void*)input,
                                              (void*)sm); 
    }
    else if(GetKeyDown(input, SDL_SCANCODE_D))
    {
        entity->xMove = 1;
        entity->yMove = 0;
        sm->ChangeState(entity->moveState, 4, (void*)entity,
                                              (void*)map,
                                              (void*)input,
                                              (void*)sm); 
    }
    else if(GetKeyDown(input, SDL_SCANCODE_W))
    {
        entity->xMove = 0;
        entity->yMove = -1;
        sm->ChangeState(entity->moveState, 4, (void*)entity,
                                              (void*)map,
                                              (void*)input,
                                              (void*)sm);    
    }
    else if(GetKeyDown(input, SDL_SCANCODE_S))
    {
        entity->xMove = 0;
        entity->yMove = 1;
        sm->ChangeState(entity->moveState, 4, (void*)entity,
                                              (void*)map,
                                              (void*)input,
                                              (void*)sm);    
    }
    
    
}

#endif
