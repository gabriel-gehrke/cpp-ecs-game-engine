#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

struct Font
{
    TTF_Font* ttf;
    int size;

    public:
        static Font load(const std::string path, int size);
};