#pragma once

#include <SDL2/SDL.h>
#include "engine/vectors.hpp"

class Input
{
    friend class Engine;

    public:
        static bool is_key_down(SDL_Keycode character);
        static bool is_key_up(SDL_Keycode character);
        static int2 mouse_position();
        static void handle_event(SDL_Event* event);
};