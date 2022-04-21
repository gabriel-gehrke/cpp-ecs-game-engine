#pragma once


#include "SDL2/SDL_image.h"
#include <string>

struct Sprite
{
    public:
        SDL_Texture* texture;
        uint width;
        uint height;

        static Sprite load(const std::string& path);
};