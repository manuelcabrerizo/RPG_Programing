#ifndef MOVESTATE_H
#define MOVESTATE_H

#include <stdio.h>
#include <cstdarg>

#include "stateMachine.h"
#include "map.h"
#include "entity.h"
#include "input.h"

void MoveStateOnEnter(va_list* valist, int num)
{

}

void MoveStateOnExit(va_list* valist, int num)
{
    Entity* entity = NULL;
    Map* map = NULL;
 
    for(int i = 0; i < num; i++)
    {
        if(i == 0)
        {
            entity = va_arg(*valist, Entity*);
        }
        if(i == 1)
        {
            map = va_arg(*valist, Map*);
        }
    }
    
    entity->tileX += entity->xMove;
    entity->tileY += entity->yMove;
    Teleport(entity, map, entity->tileX, entity->tileY);
}

void MoveStateUpdate(va_list* valist, int num, float dt)
{
    //printf("MOVE ON UPDATE\n");
    Entity* entity = NULL;
    Map* map = NULL;
    Input* input = NULL;
    StateMachineFP* sm;
 
    for(int i = 0; i < num; i++)
    {
        if(i == 0)
        {
            entity = va_arg(*valist, Entity*);
        }
        if(i == 1)
        {
            map = va_arg(*valist, Map*);
        }
        if(i == 2)
        {
            input = va_arg(*valist, Input*);
        }
        if(i == 3)
        {
            sm = va_arg(*valist, StateMachineFP*);
        }
    }

    if(entity->xMove == -1)
    {
        entity->numFrames = 4;
        entity->actualAnim = entity->leftAnim;
    }
    else if(entity->xMove == 1)
    {
        entity->numFrames = 4;
        entity->actualAnim = entity->rightAnim;
    }
    else if(entity->yMove == -1)
    {
        entity->numFrames = 4;
        entity->actualAnim = entity->upAnim;
    }
    else if(entity->yMove == 1)
    {
        entity->numFrames = 4;
        entity->actualAnim = entity->downAnim;
    }

    static float time = 0.0f;
    float xA = (float)(entity->tileX * map->tileWidth);
    float yA = (float)(entity->tileY * map->tileHeight);
    float xB = (float)((entity->tileX + entity->xMove) * map->tileWidth);
    float yB = (float)((entity->tileY + entity->yMove) * map->tileHeight);
    float xC = xB - xA;
    float yC = yB - yA;
    float rX = xA + (xC * time);
    float rY = yA + (yC * time); 
    map->x = -(int)rX;
    map->y = -(int)rY - map->tileHeight / 2;
    map->x += WNDWIDTH / 2;
    map->y += WNDHEIGHT / 2;
    if(time >= 1.0f)
    {
        time = 0.0f;
        sm->ChangeState(entity->waitState, 4, (void*)entity,
                                              (void*)map,
                                              (void*)input,
                                              (void*)sm); 
    }
    time += dt * 2.0f;
}

#endif
