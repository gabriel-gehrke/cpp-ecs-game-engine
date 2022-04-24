#include "engine/input.hpp"
#include "engine/event/event_manager.hpp"
#include <unordered_map>

static std::unordered_map<SDL_Keycode, bool> key_pressed_hashmap;

EventManager<SDL_Keycode> Input::on_key_down = EventManager<SDL_Keycode>();

void Input::handle_event(SDL_Event* event)
{
    SDL_Keycode key = event->key.keysym.sym;
    
    if (event->type == SDL_KEYDOWN)
    {
        key_pressed_hashmap.insert_or_assign(key, true);
        on_key_down.fire(key);
    }
    else if (event->type == SDL_KEYUP)
    {
        key_pressed_hashmap.insert_or_assign(key, false);
    }
}

bool Input::is_key_down(SDL_Keycode key)
{
    const auto& elem = key_pressed_hashmap.find(key);
    return (elem != key_pressed_hashmap.end()) && elem->second;
}

bool Input::is_key_up(SDL_Keycode key)
{
    return !is_key_down(key);
}

int2 Input::mouse_position()
{
    int2 pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}