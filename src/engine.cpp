#include "engine.hpp"

void Scene::add_entity(Entity* entity)
{
    this->entities.push_back(std::shared_ptr<Entity>(entity));
}

Engine::Engine() : graphics(Graphics(1280, 720)), scene(Scene(*this))
{

}

void Engine::load(Scene& scene)
{
}

void Engine::loop()
{
    SDL_Event event;

    while(!(event.type == SDL_QUIT)){
        SDL_Delay(10);  // setting some Delay

        this->graphics.clear();

        for (auto& e : this->scene.entities)
        {
            for (auto& c : e->components)
            {
                c->update();
            }
        }

        this->graphics.refresh();

        SDL_PollEvent(&event);  // Catching the poll event.
    }
}