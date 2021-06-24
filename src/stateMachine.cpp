#include "stateMachine.h"
#include "stdio.h"
#include "darray.h"

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
    ArrayPush(this->states, state, StateFP);
    if(this->states[ArrayLength(this->states) - 1].OnEnter != NULL)
    {
        this->states[ArrayLength(this->states) - 1].OnEnter(&valist, num);
    }
    else
    {
        printf("State::OnEnter::NULL::POINTER\n");
    }
    va_end(valist);
}

void StateMachineFP::PopState(int num, ...)
{
    //TODO(manuto): improve darray to handle ArrayPop().
    /*
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
    */

}

void StateMachineFP::ChangeState(StateFP state, int num, ...)
{
    va_list valist;
    va_start(valist, num);
    if(this->states[ArrayLength(this->states) - 1].OnExit != NULL)
    {

        this->states[ArrayLength(this->states) - 1].OnExit(&valist, num);
    }
    else
    { 
        printf("State::OnExit::NULL::POINTER\n");
    }
    ArrayFree(this->states);
    va_end(valist);
    va_start(valist, num);
    this->states = NULL;
    ArrayPush(this->states, state, StateFP); 
    if(this->states[ArrayLength(this->states) - 1].OnEnter != NULL)
    {
        this->states[ArrayLength(this->states) - 1].OnEnter(&valist, num);
    }
    else
    {
        printf("State::OnEnter::NULL::POINTER\n");
    }
    va_end(valist);
}

void StateMachineFP::ClearStates()
{
    ArrayFree(this->states);
    this->states = NULL;
}

void StateMachineFP::Update(float dt, int num, ...)
{
    va_list valist;
    va_start(valist, num);
    if(this->states[ArrayLength(this->states) - 1].Update != NULL)
    {
        this->states[ArrayLength(this->states) - 1].Update(&valist, num, dt);
    }
    else
    { 
        printf("State::Update::NULL::POINTER\n");
    }
    va_end(valist);
}


