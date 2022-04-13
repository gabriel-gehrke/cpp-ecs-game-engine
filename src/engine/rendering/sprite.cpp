#include "engine/rendering/sprite.hpp"
#include "engine/rendering/graphics.hpp"
#include <stdexcept>
#include <string>

Sprite Sprite::load(const char* path)
{
    Sprite s;

    // load pixels, create gpu texture, unload pixels
    SDL_Surface* temp = IMG_Load(path);
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