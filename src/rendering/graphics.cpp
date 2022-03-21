#include "rendering/graphics.hpp"
#include <iostream>


static void print_hardware()
{
    const auto drivers = SDL_GetNumVideoDrivers();
    for (auto i = 0; i < drivers; i++)
    {
        std::cout << i << ": " << SDL_GetVideoDriver(i) << std::endl;
    }
}

static volatile uint __num_graphics = 0;

Graphics::Graphics(uint w, uint h)
{
    if (__num_graphics++ == 0)
    {
        print_hardware();
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

void Graphics::set_color(const Color& color)
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

void Graphics::draw_rectangle(int x, int y, int w, int h, const Color& color)
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

void Graphics::draw_circle(int x, int y, int r, const Color& color)
{
    this->set_color(color);

    // https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
    
    const int32_t diameter = (r * 2);

    int _x = (r - 1);
    int _y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    const auto& renderer = this->renderer;

    while (_x >= _y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, x + _x, y - _y);
        SDL_RenderDrawPoint(renderer, x + _x, y + _y);
        SDL_RenderDrawPoint(renderer, x - _x, y - _y);
        SDL_RenderDrawPoint(renderer, x - _x, y + _y);
        SDL_RenderDrawPoint(renderer, x + _y, y - _x);
        SDL_RenderDrawPoint(renderer, x + _y, y + _x);
        SDL_RenderDrawPoint(renderer, x - _y, y - _x);
        SDL_RenderDrawPoint(renderer, x - _y, y + _x);

        if (error <= 0)
        {
            ++_y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --_x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void Graphics::draw_line(int x1, int y1, int x2, int y2, const Color& color)
{
    this->set_color(color);
    SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2);
}