#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>

// create tree callbacks functions 
typedef void (*OnEnterFunc)();
typedef void (*OnExitFunc)();
typedef void (*UpdateFunc)(float);

struct StateFP
{
    OnEnterFunc OnEnter;
    OnExitFunc OnExit;
    UpdateFunc Update;
};

void InitState(StateFP* state,
               OnEnterFunc OnEnter,
               OnExitFunc OnExit,
               UpdateFunc Update);

struct StateMachineFP
{
    std::vector<StateFP> states; 
    void PushState(StateFP state);
    void PopState();
    void ChangeState(StateFP state);
    void ClearStates();
    void Update(float dt);
};

#endif
