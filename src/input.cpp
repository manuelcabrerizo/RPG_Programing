#include "input.h"

void SetKeyDown(Input* input, uint32_t scanCode)
{
    input->keysDown[scanCode] = true;
    input->keysUp[scanCode] = false;
}

void SetKeyUp(Input* input, uint32_t scanCode)
{
    input->keysDown[scanCode] = false;
    input->keysUp[scanCode] = true;
}

bool GetKeyDown(Input* input, uint32_t scanCode)
{
    return input->keysDown[scanCode];
}

bool GetKeyUp(Input* input, uint32_t scanCode)
{
    input->keysUp[scanCode] = false;
    return input->keysUp[scanCode];
}


