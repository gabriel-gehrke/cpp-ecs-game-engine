#pragma once


#include "SDL_image.h"

struct Sprite
{
    public:
        SDL_Texture* texture;
        uint width;
        uint height;

        static Sprite load(const char* path);
};