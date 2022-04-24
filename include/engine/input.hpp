#pragma once

#include <SDL2/SDL.h>
#include "engine/vectors.hpp"
#include "engine/event/event_manager.hpp"

class Input
{
    friend class Engine;

    public:

        static bool is_key_down(SDL_Keycode character);
        static bool is_key_up(SDL_Keycode character);
        static int2 mouse_position();
        static void handle_event(SDL_Event* event);

        static EventManager<SDL_Keycode> on_key_down;
};