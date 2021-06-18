#include "actions.h"
#include "engine.h" 

Map* tpMap;
int* tpTileX;
int* tpTileY;

void TeleportResult(Entity* entity, int index)
{
    entity->tileX = tpTileX[index];
    entity->tileY = tpTileY[index];
    Teleport(entity, tpMap, entity->tileX, entity->tileY);
}

ReturnFunc TeleportAction(Map* map, int tileX, int tileY)
{
    tpMap = map;
    ArrayPush(tpTileX, tileX, int);
    ArrayPush(tpTileY, tileY, int);
    ReturnFunc returnFunc = TeleportResult;
    return returnFunc;   
}

void FreeGlobals()
{
    ArrayFree(tpTileX);
    ArrayFree(tpTileY);
}


