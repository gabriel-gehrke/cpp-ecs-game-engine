#include "rendering/graphics.hpp"

Color::Color(u_char grey) : Color(grey, grey, grey){}
Color::Color(u_char r, u_char g, u_char b) : Color(r, g, b, SDL_ALPHA_OPAQUE){}
Color::Color(u_char r, u_char g, u_char b, u_char a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
Color Color::black() {return Color(0,0,0);}
Color Color::white() {return Color(255,255,255);}


static volatile uint __num_graphics = 0;

Graphics::Graphics(uint w, uint h)
{
    if (__num_graphics++ == 0)
    {
        SDL_Init(SDL_INIT_VIDEO);
    }
    SDL_CreateWindowAndRenderer(w, h, 0, &this->window, &this->renderer);
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    if (--__num_graphics == 0)
    {
        SDL_Quit();
    }
}

void Graphics::set_color(Color color)
{
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

void Graphics::clear()
{
    this->set_color(Color::black());
    SDL_RenderClear(this->renderer);
}

void Graphics::refresh()
{
    SDL_RenderPresent(this->renderer);
}

void Graphics::draw_rectangle(int x, int y, int w, int h, Color color)
{
    this->set_color(color);
    SDL_Rect rect = {
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };
    SDL_RenderDrawRect(this->renderer, &rect);
}