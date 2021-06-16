#ifndef WAITSTATE_H
#define WAITSTATE_H

#include <stdio.h>
#include <cstdarg>

#include "map.h"
#include "entity.h"

void WaitStateOnEnter(va_list* valist, int num)
{
    printf("WAIT ON ENTER\n");
    printf("num: %d\n", num); 
    va_list actual_Valist = *valist; 
    Entity* entity = NULL;
    Map* map = NULL;
 
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
    }
    
    if(entity != NULL && map != NULL)
    {
        printf("MISSION::SUCCEED\n");
    }
    printf("entity Height: %d\n", entity->height);
    

}

void WaitStateOnExit(va_list* valist, int num)
{
    printf("WAIT ON EXIT\n");
}

void WaitStateUpdate(va_list* valist, int num, float dt)
{
    printf("WAIT ON UPDATE\n");
}

#endif
