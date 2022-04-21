#include "engine/engine.hpp"
#include "engine/input.hpp"
#include "engine/algebra.hpp"
#include "engine/ui/text.hpp"
#include <chrono>

Entity& Scene::new_entity()
{
    Entity* e = new Entity(*this);
    this->entities.push_back(e);
    return *e;
}

Engine::Engine() : scene(Scene(*this)), camera(10.0f)
{
    Graphics::init(1280, 720);
}

void Engine::load(Scene& scene)
{
}

static void handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Graphics::clear();
                exit(1);
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                Input::handle_event(&event);

        }
    }
}

void Engine::loop()
{   
    while (true) {
        // begin recording the frame time
        auto t_begin = std::chrono::steady_clock::now();

        this->framecounter++;
        
        Graphics::clear();
        physics.step();

        for (auto& e_ptr : this->scene.entities)
        {
            Entity& e = *e_ptr;

            for (auto& [id, component] : e)
            {
                component->update();
            }
        }

        Graphics::refresh();

        // stop time
        auto t_end = std::chrono::steady_clock::now();
        auto t_diff = t_end - t_begin;
        const auto micros = std::max((int)std::chrono::duration_cast<std::chrono::microseconds>(t_diff).count(), 1);
        const auto millis = micros / 1000;

        // calculate delta time
        this->dt = (float) micros / 1E6f;
        int fps = (int) std::round(1.0f / this->dt);
        Graphics::set_window_title((std::to_string(fps) + " fps - " + std::to_string(millis) + " ms").c_str());

        // sdl events
        handle_events();

        // keyboard test
        uint keysdown = 0;
        for (char c = 'a'; c <= 'z'; c++)
        {
            if (Input::is_key_down(c))
            {
                std::cout << c;
                keysdown++;
            }
        }
        if (keysdown > 0)
        {
            std::cout << std::endl;
        }
    }
}