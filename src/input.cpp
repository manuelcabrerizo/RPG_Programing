#include "input.h"

void SetKeyDown(Input* input, uint32_t scanCode)
{
    input->keysDown[scanCode] = true;    
}

void SetKeyUp(Input* input, uint32_t scanCode)
{
    input->keysDown[scanCode] = false;
    input->keysWasDown[scanCode] = false;
}

bool GetKeyJustDown(Input* input, uint32_t scanCode)
{
    if(input->keysDown[scanCode] && !input->keysWasDown[scanCode]) 
    {
        input->keysWasDown[scanCode] = true;
        return input->keysDown[scanCode];
    }
    else
    {
        input->keysDown[scanCode] = false;
        return input->keysDown[scanCode];
    }
}

bool GetKeyDown(Input* input, uint32_t scanCode)
{
    return input->keysDown[scanCode];
}



