#include "engine/rendering/font.hpp"
#include "engine/resources.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>

Font Font::load(const std::string path, int size)
{
    // load resource
    const Resource& res = Resource::load(path);
    SDL_RWops* io = SDL_RWFromConstMem(res.data, (int) res.size);

    // load font
    TTF_Font* ttf = TTF_OpenFontRW(io, 1, size);
    if (ttf == NULL)
    {
        throw std::invalid_argument(std::string("invalid resource: ") + std::string(path));
    }

    Font font = {.ttf = ttf, .size = size};
    return font;
}