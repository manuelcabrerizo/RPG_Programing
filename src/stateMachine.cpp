#include "stateMachine.h"

void InitState(StateFP* state,
               OnEnterFunc OnEnter,
               OnExitFunc OnExit,
               UpdateFunc Update)
{
    state->OnEnter = OnEnter;
    state->OnExit = OnExit;
    state->Update = Update;
}

void StateMachineFP::PushState(StateFP state, int num, ...)
{
    va_list valist;
    va_start(valist, num);
    this->states.push_back(state);
    state.OnEnter(&valist, num);
    va_end(valist);
}

void StateMachineFP::PopState(int num, ...)
{
    va_list valist;
    this->states.back().OnExit(&valist, num);
    this->states.pop_back();
}

void StateMachineFP::ChangeState(StateFP state, int num, ...)
{
    va_list valist;
    this->states.clear();
    this->states.push_back(state);
    state.OnEnter(&valist, num);


}

void StateMachineFP::ClearStates()
{
    this->states.clear();
}

void StateMachineFP::Update(float dt, int num, ...)
{
    va_list valist;
    this->states.back().Update(&valist, num, dt);
}


