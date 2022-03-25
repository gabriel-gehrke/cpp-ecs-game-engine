#include "engine.hpp"
#include "components/rigidbody.hpp"
#include <chrono>

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
    /*
    // triangle
    {
        Entity& e = this->scene.new_entity();
        Collider& col = e.add_component<Collider>();
        //e.add_component<Rigidbody>();
        col.add_vertex(float2(-50, -50));
        col.add_vertex(float2(100, 50));
        col.add_vertex(float2(-50, 50));
        e.position = float2(150, 150);
    }
    */

    // ground
    {
        Entity& e = this->scene.new_entity();
        Collider& col = e.add_component<Collider>();
        col.add_vertex(float2(0, 0));
        const uint num_points = 10;
        for (auto i = 0; i < num_points; i++)
        {
            float x = (1280 / (num_points + 2.0f)) * (i+1);
            float y = rand64() % 200 + 500;
            col.add_vertex(float2(x, y)); 
        }
        col.add_vertex(float2(1280, 0));
        col.add_vertex(float2(1280, 720));
        col.add_vertex(float2(0, 720));
    }

    

    /*
    // square
    {
        Entity& e = this->scene.new_entity();
        Collider& col = e.add_component<Collider>();
        col.add_vertex(float2(-50, -50));
        col.add_vertex(float2(50, -50));
        col.add_vertex(float2(50, 50));
        col.add_vertex(float2(-50, 50));
        e.add_component<Rigidbody>();
        e.get_component<Rigidbody>().bounciness = 0.8f;
        e.position = float2(1280 / 2, -100);
    }
    */
    
    
    // circles
    const uint NUM_BALLS = 20;
    const float BALL_RADIUS = 15;
    const float BALL_VERTS = 5;

    for (auto i = 0; i < NUM_BALLS; i++)
    {
        float posX = (1280 / (NUM_BALLS + 2)) * (i + 1);
        float posY = randrange(100, 500);

        Entity& e = this->scene.new_entity();
        e.add_component<Rigidbody>();
        e.get_component<Rigidbody>().bounciness = 0.95f;
        e.position = float2(posX, posY);

        Collider& col = e.add_component<Collider>();

        for (auto i = 0; i < BALL_VERTS; i++)
        {
            float angle = ((M_PI * 2) / BALL_VERTS) * i;
            float x = std::sin(angle) * BALL_RADIUS;
            float y = std::cos(angle) * BALL_RADIUS;
            col.add_vertex(float2(x, y));
        }
    }
    

    SDL_Event event;
    
    while(!(event.type == SDL_QUIT)){
        // begin recording the frame time
        auto t_begin = std::chrono::steady_clock::now();

        this->framecounter++;
        this->graphics.clear();
        physics.step();

        for (auto& e_ptr : this->scene.entities)
        {
            Entity& e = *e_ptr;

            for (auto& [id, component] : e)
            {
                component->update();
            }
        }

        this->graphics.refresh();

        // stop time
        auto t_end = std::chrono::steady_clock::now();
        auto t_diff = t_end - t_begin;
        const auto micros = std::max((int)std::chrono::duration_cast<std::chrono::microseconds>(t_diff).count(), 1);
        const auto millis = micros / 1000;

        // calculate delta time
        this->dt = (float) micros / 1E6f;
        int fps = (int) std::round(1.0f / this->dt);
        this->graphics.set_window_title((std::to_string(fps) + " fps - " + std::to_string(millis) + " ms").c_str());

        // poll event
        SDL_PollEvent(&event);
    }
}