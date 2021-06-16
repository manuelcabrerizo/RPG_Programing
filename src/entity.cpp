#include "entity.h"
#include "engine.h"

#include "waitState.h"
#include "moveState.h"

void LoadEntity(Entity* entity, const char* textureFilePath)
{
    entity->width = 16;
    entity->height = 24;
    entity->tileX = 10;
    entity->tileY = 2;
    entity->frame = 0;
    entity->image = LoadTexture(textureFilePath);
    entity->uvs = GenerateUVs(entity->image,
                              entity->width,
                              entity->height);

    InitState(&entity->waitState, WaitStateOnEnter, WaitStateOnExit, WaitStateUpdate);
    InitState(&entity->moveState, MoveStateOnEnter, MoveStateOnExit, MoveStateUpdate);
}

void SetEntityFrame(Entity* entity, int frame)
{
    entity->frame = frame;
}

int2 GetTileFoot(Map* map, int x, int y)
{
    int2 result = {};
    result.a = map->x + (x * map->tileWidth);
    result.b = map->y + (y * map->tileHeight) - map->tileHeight / 2;
    return result;
}

void Teleport(Entity* entity, Map* map, int tileX, int tileY)
{
    int2 result = GetTileFoot(map, tileX, tileY);
    entity->x = result.a;
    entity->y = result.b;
}
