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

void StateMachineFP::PushState(StateFP state)
{
    this->states.push_back(state);
    state.OnEnter();
}

void StateMachineFP::PopState()
{
    this->states.back().OnExit();
    this->states.pop_back();
}

void StateMachineFP::ChangeState(StateFP state)
{
    this->states.back().OnExit();
    this->states.clear();
    this->PushState(state);
}

void StateMachineFP::ClearStates()
{
    this->states.back().OnExit();
    this->states.clear();
}

void StateMachineFP::Update(float dt)
{
    this->states.back().Update(dt);
}


