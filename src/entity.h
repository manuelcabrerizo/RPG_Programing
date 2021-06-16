#ifndef ENTITY_H
#define ENTITY_H

#include "texture.h"
#include "map.h"

#include "stateMachine.h"

struct int2
{
    int a;
    int b;
};

struct Entity
{
    int x;
    int y;
    int tileX;
    int tileY;
    int width;
    int height;
    int frame;
    Texture image;
    float* uvs;
    
    StateFP waitState;
    StateFP moveState;

    int xMove;
    int yMove;

    int* actualAnim;
    int numFrames;
    int upAnim[4];
    int downAnim[4];
    int leftAnim[4];
    int rightAnim[4];
};

void UpdateEntityAnim(Entity* entity, float dt);
void SetEntityFrame(Entity* entity, int frame);
void LoadEntity(Entity* entity, const char* textureFilePath);
int2 GetTileFoot(Map* map, int x, int y);
void Teleport(Entity* entity, Map* map, int tileX, int tileY);

#endif
