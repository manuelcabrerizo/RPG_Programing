#ifndef ENTITY_H
#define ENTITY_H

#include "texture.h"
//#include "map.h"
#include <string>

#include "stateMachine.h"

struct int2
{
    int a;
    int b;
};

struct Entity
{
    int type;
    int x;
    int y;
    int tileX;
    int tileY;
    int width;
    int height;
    int frame;
    char facing;
    Texture image;
    float* uvs;
    int layer;

    // entity movement
    float animTime;
    float time;
    float frameCount;
    float countDown;
    
    std::string defStateName;
    StateFP defaultState; 
    StateFP waitState;
    StateFP moveState;
    StateFP npcStandState;
    StateFP planStrollState;

    int xMove;
    int yMove;

    int* actualAnim;
    int numFrames;
    int upAnim[4];
    int downAnim[4];
    int leftAnim[4];
    int rightAnim[4];

    StateMachineFP sm;
};


typedef void (*ReturnFunc)(Entity* entity, int index);

struct Trigger
{
    ReturnFunc OnEnter;
    ReturnFunc OnExit;
    ReturnFunc OnUse;
    int index;
};

struct Map;

void UpdateEntityAnim(Entity* entity, float dt);
void SetEntityFrame(Entity* entity, int frame);
void LoadEntity(Entity* entity, const char* textureFilePath);
int2 GetTileFoot(Map* map, int x, int y);
int2 GetFacedTileCoords(Entity* entity);
void Teleport(Entity* entity, Map* map, int tileX, int tileY);
std::vector<Entity> LoadEntitiesFromLuaFile(const char* filePath);
#endif
