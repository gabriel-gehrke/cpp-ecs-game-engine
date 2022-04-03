#pragma once

#include <SDL2/SDL.h>

class Input
{
    friend class Engine;

    public:
        static bool is_key_down(SDL_Keycode character);
        static bool is_key_up(SDL_Keycode character);
        static void handle_event(SDL_Event* event);
};