#include "engine/rendering/sprite.hpp"
#include "engine/rendering/graphics.hpp"
#include "engine/resources.hpp"
#include <stdexcept>

Sprite Sprite::load(const std::string& path)
{
    Sprite s;

    // load resource
    const Resource& res = Resource::load(path);
    SDL_RWops* io = SDL_RWFromConstMem(res.data, (int) res.size);

    // load pixels, create gpu texture, unload pixels
    SDL_Surface* temp = IMG_Load_RW(io, 1);
    if (temp == NULL)
    {
        throw std::invalid_argument(std::string("invalid resource: ") + std::string(path));
    }
    s.width = temp->w;
    s.height = temp->h;
    s.texture = Graphics::create_texture(temp);
    SDL_FreeSurface(temp);
    
    return s;
}