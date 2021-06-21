#include "entity.h"
#include "engine.h"
#include "waitState.h"
#include "moveState.h"
#include "npcStandState.h"
#include "planStrollState.h"

#include <stdlib.h> 

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

std::vector<Entity> LoadEntitiesFromLuaFile(const char* filePath)
{
    sol::state lua; 
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    lua.script_file(filePath); 
    sol::table luaEntities = lua["gEntities"];
    std::vector<Entity> entities;
    int index = 0;
    while(true)
    {
        sol::optional<sol::table> exist_entity = luaEntities[index];
        if(exist_entity == sol::nullopt)
        {
            break;
        }
        else
        {
            Entity entity = {};
            sol::table entityTable = luaEntities[index];

            entity.frame = (int)entityTable["frame"]; 
            entity.width = (int)entityTable["width"];
            entity.height = (int)entityTable["height"];
            entity.tileX = (int)entityTable["tileX"];
            entity.tileY = (int)entityTable["tileY"];
            std::string facingString = entityTable["facing"];
            entity.facing = (char)facingString.c_str()[0];
            std::string typeString = entityTable["type"];
            entity.type = (char)typeString.c_str()[0];
            entity.x = entity.tileX * entity.width;
            entity.y = entity.tileY * entity.width; 
            std::string texturePath = entityTable["texture"];
            entity.image = LoadTexture(texturePath.c_str());
            entity.uvs = GenerateUVs(entity.image,
                                      entity.width,
                                      entity.height);
            entity.layer = (int)entityTable["layer"];

            for(int i = 0; i < 4; i++)
            {
                entity.upAnim[i]    = (int)entityTable["anims"]["up"][i + 1] - 1;
                entity.rightAnim[i] = (int)entityTable["anims"]["right"][i + 1] - 1;
                entity.downAnim[i]  = (int)entityTable["anims"]["down"][i + 1] - 1;
                entity.leftAnim[i]  = (int)entityTable["anims"]["left"][i + 1] - 1;
            } 
            entity.numFrames = 4;

            for(int i = 0; i < (int)entityTable["numberOfStates"]; i++)
            {
                std::string stateName = entityTable["controller"][i + 1];
                if(strcmp(stateName.c_str(), "wait") == 0)
                {
                    InitState(&entity.waitState, WaitStateOnEnter, WaitStateOnExit, WaitStateUpdate);
                }
                else if(strcmp(stateName.c_str(), "move") == 0)
                {
                    InitState(&entity.moveState, MoveStateOnEnter, MoveStateOnExit, MoveStateUpdate);
                }
                else if(strcmp(stateName.c_str(), "npc_stand") == 0)
                {
                    InitState(&entity.npcStandState, StandStateOnEnter, StandStateOnExit, StandStateUpdate);
                }
                else if(strcmp(stateName.c_str(), "plan_stroll") == 0)
                {
                    InitState(&entity.planStrollState, PlanStrollOnEnter, PlanStrollOnExit, PlanStrollUpdate);
                }
            }
            
            std::string temp = entityTable["state"];
            entity.defStateName = temp;
 
            if(entity.facing == 'd')
            {
                entity.actualAnim = entity.downAnim;
            }
            else if(entity.facing == 'u')
            {
                entity.actualAnim = entity.upAnim;
            }
            else if(entity.facing == 'l')
            {
                entity.actualAnim = entity.leftAnim;
            }
            else if(entity.facing == 'r')
            {
                entity.actualAnim = entity.rightAnim;
            }

            entities.push_back(entity);
        }
        index++;
    }
    return entities;
}

void UpdateEntityAnim(Entity* entity, float dt)
{
    if(entity->numFrames > 1)
    {
        entity->animTime += dt * 10.0f;
        if(entity->animTime >= entity->numFrames)
        {
            entity->animTime = 0.0f;
        }
    }
    SetEntityFrame(entity, entity->actualAnim[(int)entity->animTime]);
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
    if(entity->type == 'h')
    {
        entity->x = entity->tileX * entity->width;
        entity->y = entity->tileY * entity->width;
        map->x = -(int)entity->x;
        map->y = -(int)entity->y - map->tileHeight / 2;
        map->x += WNDWIDTH  / 2;
        map->y += WNDHEIGHT / 2; 
    }
    int2 result = GetTileFoot(map, tileX, tileY);
    entity->x = result.a;
    entity->y = result.b;    
}
