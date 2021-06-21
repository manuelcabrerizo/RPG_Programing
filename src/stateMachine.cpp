#include "stateMachine.h"
#include "stdio.h"

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
    if(this->states.back().OnEnter != NULL)
    {
        this->states.back().OnEnter(&valist, num);
    }
    else
    {
        printf("State::OnEnter::NULL::POINTER\n");
    }
    va_end(valist);
}

void StateMachineFP::PopState(int num, ...)
{
    va_list valist;
    va_start(valist, num);
    if(this->states.back().OnExit != NULL)
    {
        this->states.back().OnExit(&valist, num);
    }
    else
    { 
        printf("State::OnExit::NULL::POINTER\n");
    }
    this->states.pop_back();
    va_end(valist);

}

void StateMachineFP::ChangeState(StateFP state, int num, ...)
{
    va_list valist;
    va_start(valist, num);
    if(this->states.back().OnExit != NULL)
    {
        this->states.back().OnExit(&valist, num);
    }
    else
    { 
        printf("State::OnExit::NULL::POINTER\n");
    }
    this->states.clear();
    va_end(valist);
    va_start(valist, num);
    this->states.push_back(state);
    if(this->states.back().OnEnter != NULL)
    {
        this->states.back().OnEnter(&valist, num);
    }
    else
    {
        printf("State::OnEnter::NULL::POINTER\n");
    }
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
    if(this->states.back().Update != NULL)
    {
        this->states.back().Update(&valist, num, dt);
    }
    else
    { 
        printf("State::Update::NULL::POINTER\n");
    }
    va_end(valist);
}


