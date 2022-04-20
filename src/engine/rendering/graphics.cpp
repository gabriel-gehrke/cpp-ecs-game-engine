#include "engine/rendering/graphics.hpp"
#include <iostream>

static SDL_Window* window;
static SDL_Renderer* renderer;
static Color background = Color::black();

static uint width;
static uint height;

static void set_color(const Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Graphics::init(uint w, uint h)
{
    width = w;
    height = h;

    // init video hardware and all image formats
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(0b1111);
    TTF_Init();

    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}

int2 Graphics::get_size()
{
    return int2((int)width, (int)height);
}

void Graphics::close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::clear()
{
    set_color(background);
    SDL_RenderClear(renderer);
}

void Graphics::refresh()
{
    SDL_RenderPresent(renderer);
}

void Graphics::set_window_title(const char* s)
{
    SDL_SetWindowTitle(window, s);
}

void Graphics::draw_rectangle(int x, int y, int w, int h, const Color& color)
{
    set_color(color);
    SDL_Rect rect = {
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };
    SDL_RenderDrawRect(renderer, &rect);
}

void Graphics::draw_circle(int x, int y, int r, const Color& color)
{
    set_color(color);

    // https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
    
    const int32_t diameter = (r * 2);

    int _x = (r - 1);
    int _y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

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
    set_color(color);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Graphics::draw_sprite(const Sprite* sprite, int x1, int y1, int x2, int y2, float rotation)
{
    const SDL_Rect src = {
        .x = 0, 
        .y = 0, 
        .w = (int) sprite->width, 
        .h = (int) sprite->height
    };
    const SDL_Rect dest = {
        .x = x1,
        .y = y1,
        .w = x2 - x1,
        .h = y2 - y1
    };

    // draw with default rotation center point (NULL)
    SDL_RenderCopyEx(renderer, sprite->texture, &src, &dest, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

SDL_Texture* Graphics::create_texture(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(renderer, surface);
}

void Graphics::draw_texture(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest)
{
    SDL_RenderCopy(renderer, texture, &src, &dest);
}