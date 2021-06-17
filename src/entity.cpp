#include "entity.h"
#include "engine.h"

#include "waitState.h"
#include "moveState.h"

void LoadEntity(Entity* entity, const char* textureFilePath)
{
    entity->width = 16;
    entity->height = 24;
    entity->tileX = 9;
    entity->tileY = 2;
    entity->facing = 'd';
    entity->x = entity->tileX * entity->width;
    entity->y = entity->tileY * entity->width;
    entity->frame = 0;
    entity->image = LoadTexture(textureFilePath);
    entity->uvs = GenerateUVs(entity->image,
                              entity->width,
                              entity->height);
    entity->layer = 0;
    for(int i = 0; i < 4; i++)
    {
        entity->upAnim[i] = i;
        entity->rightAnim[i] = i + 4;
        entity->downAnim[i] = i + 8;
        entity->leftAnim[i] = i + 12;
    }
    entity->actualAnim = entity->downAnim;
    entity->numFrames = 4;

    InitState(&entity->waitState, WaitStateOnEnter, WaitStateOnExit, WaitStateUpdate);
    InitState(&entity->moveState, MoveStateOnEnter, MoveStateOnExit, MoveStateUpdate);
}

void UpdateEntityAnim(Entity* entity, float dt)
{
    static float time = 0.0f; 
    if(entity->numFrames > 1)
    {
        time += dt * 10.0f;
        if(time >= entity->numFrames)
        {
            time = 0.0f;
        }
    }
    SetEntityFrame(entity, entity->actualAnim[(int)time]);
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

int2 GetFacedTileCoords(Entity* entity)
{
    int xInc = 0;
    int yInc = 0;

    if(entity->facing == 'l')
    {
        xInc = -1;
    }
    else if(entity->facing == 'r')
    {
        xInc = 1;
    }
    else if(entity->facing == 'u')
    {
        yInc = -1;
    }
    else if(entity->facing == 'd')
    {
        yInc = 1;
    }

    int2 result = {};
    result.a = entity->tileX + xInc;
    result.b = entity->tileY + yInc;
    return result;  
}

void Teleport(Entity* entity, Map* map, int tileX, int tileY)
{
    int2 result = GetTileFoot(map, tileX, tileY);
    entity->x = result.a;
    entity->y = result.b;
}
