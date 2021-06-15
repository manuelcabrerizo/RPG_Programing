#ifndef MOVESTATE_H
#define MOVESTATE_H

#include "stateMachine.h"
#include "entity.h"

struct MoveState : public State
{
    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update();
    Entity* entity;
    Map* map;
};


#endif
