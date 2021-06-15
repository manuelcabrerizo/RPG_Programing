#include "stateMachine.h"
#include "darray.h"


void ChageState(StateMachine* stateMachine, State* state)
{
    stateMachine->states[stateMachine->numberOfStates - 1]->OnExit();
    ArrayFree(stateMachine->states);
    stateMachine->states = 0;
    stateMachine->numberOfStates = 0;
    PushSate(stateMachine, state);
}

void PushSate(StateMachine* stateMachine, State* state)
{
    ArrayPush(stateMachine->states, state, State*);
    stateMachine->numberOfStates++;
    stateMachine->states[stateMachine->numberOfStates - 1]->OnEnter();
}

void PopState(StateMachine* stateMachine)
{
    stateMachine->states[stateMachine->numberOfStates - 1]->OnExit();
}

void UpdateStateMachine(StateMachine* stateMachine)
{
    stateMachine->states[stateMachine->numberOfStates - 1]->Update();
}


