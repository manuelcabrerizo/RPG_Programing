#ifndef STATEMACHINE_H
#define STATEMACHINE_H

/*
#define PushSate(stateMachine, state, type) \
    do { \
       ArrayPushState(stateMachine.states, state, type); \
       stateMachine.numberOfStates++; \
       stateMachine.states[stateMachine.numberOfStates - 1]->OnEnter(); \
    } while (0); 
*/
struct State
{
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual void Update() = 0;
};

struct StateMachine
{
    State** states;
    int numberOfStates;
};

void PushSate(StateMachine* stateMachine, State* state);
void PopState(StateMachine* stateMachine);
void ChageState(StateMachine* stateMachine, State* state);
void UpdateStateMachine(StateMachine* stateMachine);

#endif
