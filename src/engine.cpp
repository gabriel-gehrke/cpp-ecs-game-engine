#include "engine.hpp"
#include "components/rigidbody.hpp"

Entity& Scene::new_entity()
{
    Entity* e = new Entity(*this);
    this->entities.push_back(std::unique_ptr<Entity>(e));
    return *e;
}

Engine::Engine() : graphics(Graphics(1280, 720)), scene(Scene(*this))
{

}

void Engine::load(Scene& scene)
{
}

void Engine::loop()
{
    // triangle
    {
        Entity& e = this->scene.new_entity();
        Collider& col = e.add_component<Collider>();
        e.add_component<Rigidbody>();
        col.add_vertex(float2(-50, -50));
        col.add_vertex(float2(100, 50));
        col.add_vertex(float2(-50, 50));
        e.position = float2(150, 150);
    }
    

    // square
    Entity& e = this->scene.new_entity();
    Collider& col = e.add_component<Collider>();
    col.add_vertex(float2(-50, -50));
    col.add_vertex(float2(50, -50));
    col.add_vertex(float2(50, 50));
    col.add_vertex(float2(-50, 50));
    e.add_component<Rigidbody>();
    e.position = float2(350, 150);

    SDL_Event event;

    while(!(event.type == SDL_QUIT)){

        SDL_Delay(10);  // setting some Delay
        this->graphics.clear();

        physics.step();

        const float speed = 2;

        if (event.type == SDL_KEYDOWN)
        {
            Rigidbody& rb = e.get_component<Rigidbody>();
            auto code = event.key.keysym.scancode;

            rb.velocity.y = -speed * (code == SDL_SCANCODE_W) + speed * (code == SDL_SCANCODE_S);
            rb.velocity.x = -speed * (code == SDL_SCANCODE_A) + speed * (code == SDL_SCANCODE_D);
        }

        for (auto& e_ptr : this->scene.entities)
        {
            Entity& e = *e_ptr;

            for (auto& [id, component] : e)
            {
                component->update();
            }
        }

        this->graphics.refresh();

        SDL_PollEvent(&event);  // Catching the poll event.
    }
}