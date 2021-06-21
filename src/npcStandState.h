#ifndef NPCSTANDSTATE_H
#define NPCSTANDSTATE_H

#include <stdio.h>
#include <cstdarg>

#include "stateMachine.h"
#include "map.h"
#include "entity.h"
#include "input.h"

void StandStateOnEnter(va_list* valist, int num)
{
    Entity* entity = NULL;

    for(int i = 0; i < num; i++)
    {
        if(i == 0)
        {
            entity = va_arg(*valist, Entity*);
        }
    } 
    entity->numFrames = 1;
}

void StandStateOnExit(va_list* valist, int num)
{
}

void StandStateUpdate(va_list* valist, int num, float dt)
{
    Entity* entity = NULL;
    Map* map = NULL;
    Input* input = NULL;
    StateMachineFP* sm = NULL;

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
    Teleport(entity, map, entity->tileX, entity->tileY);
     
   
}

#endif
