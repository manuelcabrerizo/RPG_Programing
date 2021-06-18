#ifndef ACTIONS_H
#define ACTIONS_H

#include "map.h"

void TeleportResult(Entity* entity, int index);
ReturnFunc TeleportAction(Map* map, int tileX, int tileY);
void FreeGlobals();

#endif
