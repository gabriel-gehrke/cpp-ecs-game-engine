#include "engine/ui/text.hpp"
#include <stdexcept>

void UIText::rerender()
{
    // free previously cached resources
    if (this->cached_font != NULL)
    {
        TTF_CloseFont(this->cached_font);
    }
    if (this->cached_texture != NULL)
    {
        SDL_DestroyTexture(this->cached_texture);
    }

    // load font
    SDL_RWops* io = SDL_RWFromConstMem(this->font_resource->data, (int) this->font_resource->size);
    this->cached_font = TTF_OpenFontRW(io, 1, this->font_size);
    if (this->cached_font == NULL)
    {
        throw std::invalid_argument(std::string("invalid resource: ") + std::string(this->font_resource->path));
    }

    // render font
    SDL_Surface* surface = TTF_RenderText_Blended(this->cached_font, this->text.c_str(), *((SDL_Color*)&this->color));
    if (surface == NULL)
    {
        throw std::runtime_error(std::string("error during text rendering: ") + std::string(TTF_GetError()));
    }
    this->texture_size = int2(surface->w, surface->h);
    this->cached_texture = Graphics::create_texture(surface);
    if (this->cached_texture == NULL)
    {
        throw std::runtime_error(std::string("error during text rendering: ") + std::string(TTF_GetError()));
    }
    SDL_FreeSurface(surface);
}

void UIText::set_text(const std::string& text)
{
    this->text = text;
    rerender();
}

void UIText::set_font_resource(const Resource& resource)
{
    this->font_resource = &resource;
    rerender();
}

void UIText::set_font_size(int size)
{
    if (this->font_size == size) return;

    this->font_size = size;
    rerender();
}

void UIText::set_color(const Color& color)
{
    this->color = color;
    rerender();
}

void UIText::update()
{
    if (this->cached_texture == NULL)
    {
        throw std::runtime_error(std::string("UIText texture is NULL!"));
    }

    // apply alignment
    const int2& size = this->texture_size;
    const int2 hsize = this->texture_size / 2;
    const int hor = this->alignment & 0b0011;
    const int vert = this->alignment & 0b1100;
    int2 pos = this->screen_position;
    pos.x -= hsize.x * (hor == CENTER) + size.x * (hor == RIGHT);
    pos.y -= hsize.y * (vert == CENTER) + size.y * (vert == BOTTOM);

    const auto& w = this->texture_size.x;
    const auto& h = this->texture_size.y;
    const SDL_Rect src = {0, 0, w, h};
    const SDL_Rect dest = {pos.x, pos.y, w, h};

    Graphics::draw_texture(this->cached_texture, src, dest);
}
