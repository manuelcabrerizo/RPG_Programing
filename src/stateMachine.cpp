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
    this->states.back().OnEnter(&valist, num);
    va_end(valist);
}

void StateMachineFP::PopState(int num, ...)
{
    va_list valist;
    va_start(valist, num);
    this->states.back().OnExit(&valist, num);
    this->states.pop_back();
    va_end(valist);

}

void StateMachineFP::ChangeState(StateFP state, int num, ...)
{
    va_list valist;
    va_start(valist, num);
    this->states.back().OnExit(&valist, num);
    this->states.clear();
    this->states.push_back(state);
    this->states.back().OnEnter(&valist, num);
    va_end(valist);
}

void StateMachineFP::ClearStates()
{
    this->states.clear();
}

void StateMachineFP::Update(float dt, int num, ...)
{
    va_list valist;
    va_start(valist, num);
    this->states.back().Update(&valist, num, dt);
    va_end(valist);
}


