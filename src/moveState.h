#ifndef MOVESTATE_H
#define MOVESTATE_H

#include <stdio.h>

void MoveStateOnEnter()
{
    printf("MOVE ON ENTER\n");
}

void MoveStateOnExit()
{
    printf("MOVE ON EXIT\n");
}

void MoveStateUpdate(float dt)
{
    printf("MOVE ON UPDATE\n");
}

#endif
