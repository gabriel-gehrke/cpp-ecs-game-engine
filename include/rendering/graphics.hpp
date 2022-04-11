#pragma once
#include "vectors.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Color
{
    public:
        Color(u_char grey) : r(grey), g(grey), b(grey), a(SDL_ALPHA_OPAQUE) {}
        Color(u_char r, u_char g, u_char b) : r(r), g(g), b(b), a(SDL_ALPHA_OPAQUE) {}
        Color(u_char r, u_char g, u_char b, u_char a) : r(r), g(g), b(b), a(a) {}

        static Color black() {return Color(0,0,0);}
        static Color white() {return Color(255,255,255);}

        u_char r;
        u_char g;
        u_char b;
        u_char a;
};

class Graphics
{
    public:
        static void init(uint w, uint h);
        static void close();

        static void refresh();
        static void clear();

        static void set_window_title(const char* s);
        static void draw_rectangle(int x, int y, int w, int h, const Color& color);
        static void draw_circle(int x, int y, int r, const Color& color);
        static void draw_line(int x1, int y1, int x2, int y2, const Color& color);

        static int2 get_size();

        static SDL_Texture* create_texture(SDL_Surface* surface);
};