#ifndef WAITSTATE_H
#define WAITSTATE_H


#include "stateMachine.h"
#include "entity.h"

struct WaitState : public State
{
    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update();
    Entity* entity;
    Map* map;
};

#endif
