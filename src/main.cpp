#include "simd.hpp"
#include "rendering/graphics.hpp"
#include "random.hpp"
#include <SDL2/SDL.h>
#include <iostream>

int main()
{
    Graphics g = Graphics(400, 200);

    SDL_Event event;

    uint x = 200 - 25;

    while(!(event.type == SDL_QUIT)){
        SDL_Delay(10);  // setting some Delay

        g.clear();

        g.draw_rectangle(x, 20, 50, 50, Color(255, 0, 0));
        x += (rand() % 3) - 1;

        g.refresh();
        SDL_PollEvent(&event);  // Catching the poll event.
    }

    return 0;
}