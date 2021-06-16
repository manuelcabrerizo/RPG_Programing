#ifndef MOVESTATE_H
#define MOVESTATE_H

#include <stdio.h>
#include <cstdarg>

#include "map.h"
#include "entity.h"

void MoveStateOnEnter(va_list* valist, int num)
{
    printf("MOVE ON ENTER\n"); 
}

void MoveStateOnExit(va_list* valist, int num)
{
    printf("MOVE ON EXIT\n");
}

void MoveStateUpdate(va_list* valist, int num, float dt)
{
    printf("MOVE ON UPDATE\n");
}

#endif
