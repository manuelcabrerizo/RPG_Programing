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
    StateMachine controller;
};


void SetEntityFrame(Entity* entity, int frame);
void LoadEntity(Entity* entity, const char* textureFilePath);
int2 GetTileFoot(Map* map, int x, int y);
void Teleport(Entity* entity, Map* map, int tileX, int tileY);



#endif
