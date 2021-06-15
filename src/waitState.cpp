#include "waitState.h"


#include <stdio.h>

void WaitState::OnEnter()
{
    printf("Entrando WAIT_STATE\n");
}

void WaitState::OnExit()
{
    printf("Saliendo WAIT_STATE\n");
}

void WaitState::Update()
{

}

