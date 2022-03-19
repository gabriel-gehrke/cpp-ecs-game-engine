#pragma once
#include <SDL2/SDL.h>

struct Color
{
    public:
        Color(u_char grey);
        Color(u_char r, u_char g, u_char b);
        Color(u_char r, u_char g, u_char b, u_char a);

        static Color black();
        static Color white();

        u_char r;
        u_char g;
        u_char b;
        u_char a;
};

class Graphics
{
    public:
        Graphics(uint w, uint h);
        ~Graphics();

        void refresh();
        void clear();

        void draw_rectangle(int x, int y, int w, int h, Color color);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        void set_color(Color color);
};