#ifndef WAITSTATE_H
#define WAITSTATE_H

#include <stdio.h>

void WaitStateOnEnter()
{
    printf("WAIT ON ENTER\n");
}

void WaitStateOnExit()
{
    printf("WAIT ON EXIT\n");
}

void WaitStateUpdate(float dt)
{
    printf("WAIT ON UPDATE\n");
}

#endif
