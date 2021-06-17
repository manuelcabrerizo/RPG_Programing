#ifndef ACTIONS_H
#define ACTIONS_H

#include "map.h"


Map* tpMap;
int* tpTileX;
int* tpTileY;

void TeleportResult(Entity* entity, int index)
{
    entity->tileX = tpTileX[index];
    entity->tileY = tpTileY[index];
    entity->x = entity->tileX * entity->width;
    entity->y = entity->tileY * entity->width; 
    tpMap->x = -(int)entity->x;
    tpMap->y = -(int)entity->y - tpMap->tileHeight / 2;
    tpMap->x += WNDWIDTH  / 2;
    tpMap->y += WNDHEIGHT / 2; 

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


#endif
