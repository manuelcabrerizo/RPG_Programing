#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>
#include <cstdarg>
using namespace std;

// create tree callbacks functions 
typedef void (*OnEnterFunc)(va_list* valist, int num);
typedef void (*OnExitFunc)(va_list* valist, int num);
typedef void (*UpdateFunc)(va_list* valist, int num, float dt);

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
    void PushState(StateFP state, int num, ...);
    void PopState(int num, ...);
    void ChangeState(StateFP state, int num, ...);
    void ClearStates();
    void Update(float dt, int num, ...);
};

#endif
