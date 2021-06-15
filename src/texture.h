#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>

struct Texture
{
    uint32_t* pixels;
    int width;
    int height;
};

Texture LoadTexture(const char* filePath);

#endif
