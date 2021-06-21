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
        entity->facing = 'l';
    }
    else if(entity->xMove == 1)
    {
        entity->numFrames = 4;
        entity->actualAnim = entity->rightAnim;
        entity->facing = 'r';
    }
    else if(entity->yMove == -1)
    {
        entity->numFrames = 4;
        entity->actualAnim = entity->upAnim;
        entity->facing = 'u';
    }
    else if(entity->yMove == 1)
    {
        entity->numFrames = 4;
        entity->actualAnim = entity->downAnim;
        entity->facing = 'd';
    }

    int targetX = entity->tileX + entity->xMove;
    int targetY = entity->tileY + entity->yMove;
    
    if(IsBlocked(map, targetX, targetY, 0))
    {
        entity->xMove = 0;
        entity->yMove = 0;
        sm->ChangeState(*entity->defaultState, 4, (void*)entity,
                                              (void*)map,
                                              (void*)input,
                                              (void*)sm);  
    }    
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
        
    if(entity->xMove != 0 || entity->yMove != 0)
    {
        Trigger trigger = GetTrigger(map, entity->tileX, entity->tileY, entity->layer);
        if(trigger.OnExit != NULL)
        {
            trigger.OnExit(entity, trigger.index);
        }
    }

    entity->tileX += entity->xMove;
    entity->tileY += entity->yMove;
    Teleport(entity, map, entity->tileX, entity->tileY);
    Trigger trigger = GetTrigger(map, entity->tileX, entity->tileY, entity->layer);
    if(trigger.OnEnter != NULL)
    {
        trigger.OnEnter(entity, trigger.index);
    }

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

    //entity->time = 0.0f;
    float xA = (float)(entity->tileX * map->tileWidth);
    float yA = (float)(entity->tileY * map->tileHeight);
    float xB = (float)((entity->tileX + entity->xMove) * map->tileWidth);
    float yB = (float)((entity->tileY + entity->yMove) * map->tileHeight);
    float xC = xB - xA;
    float yC = yB - yA;
    float rX = xA + (xC * entity->time);
    float rY = yA + (yC * entity->time);
    if(entity->type == 'h')
    {
        map->x = -(int)rX;
        map->y = -(int)rY - map->tileHeight / 2;
        map->x += WNDWIDTH / 2;
        map->y += WNDHEIGHT / 2;
    }
    else if(entity->type == 'n')
    {
        entity->x = (int)rX + map->x;
        entity->y = ((int)rY - map->tileHeight / 2) + map->y;
    }

    if(entity->time >= 1.0f)
    {
        entity->time = 0.0f;
        sm->ChangeState(*entity->defaultState, 4, (void*)entity,
                                              (void*)map,
                                              (void*)input,
                                              (void*)sm); 
    }
    entity->time += dt * 2.0f;
}

#endif
