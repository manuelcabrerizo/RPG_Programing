#ifndef PLANSTROLLSTATE_H
#define PLANSTROLLSTATE_H

#include <stdio.h>
#include <cstdarg>

#include "stateMachine.h"
#include "map.h"
#include "entity.h"
#include "input.h"
#include "time.h"

const float frameResetSpeed = 0.05f;


void PlanStrollOnEnter(va_list* valist, int num)
{
    Entity* entity = NULL;
    for(int i = 0; i < num; i++)
    {
        if(i == 0)
        {
            entity = va_arg(*valist, Entity*);
        }
    }
    int tempRand = rand() % 4;
    entity->countDown = (float)tempRand;
    entity->numFrames = 1;
}

void PlanStrollOnExit(va_list* valist, int num)
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
}

void PlanStrollUpdate(va_list* valist, int num, float dt)
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
    entity->countDown -= dt;
    if(entity->countDown <= 0.0f)
    {
        int choice = rand() % 4;
        if(choice == 0)
        {
            entity->xMove = -1;
            entity->yMove = 0;
            sm->ChangeState(entity->moveState, 4, (void*)entity,
                                                  (void*)map,
                                                  (void*)input,
                                                  (void*)sm); 
        }
        else if(choice == 1)
        {
            entity->xMove = 1;
            entity->yMove = 0;
            sm->ChangeState(entity->moveState, 4, (void*)entity,
                                                  (void*)map,
                                                  (void*)input,
                                                  (void*)sm); 
        }
        else if(choice == 2)
        {
            entity->xMove = 0;
            entity->yMove = -1;
            sm->ChangeState(entity->moveState, 4, (void*)entity,
                                                  (void*)map,
                                                  (void*)input,
                                                  (void*)sm); 
        }
        else if(choice == 3)
        {
            entity->xMove = 0;
            entity->yMove = 1;
            sm->ChangeState(entity->moveState, 4, (void*)entity,
                                                  (void*)map,
                                                  (void*)input,
                                                  (void*)sm); 
        }
    }

    if(entity->frameCount != -1.0f)
    {
        entity->frameCount += dt;
        if(entity->frameCount >= frameResetSpeed)
        {
            entity->frameCount = -1.0f;
        }
    }

    Teleport(entity, map, entity->tileX, entity->tileY);
     
}

#endif
