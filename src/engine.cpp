#include "engine.hpp"
#include "components/rigidbody.hpp"
#include "input.hpp"
#include "algebra.hpp"
#include <chrono>

Entity& Scene::new_entity()
{
    Entity* e = new Entity(*this);
    this->entities.push_back(std::unique_ptr<Entity>(e));
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
        col.add_vertex(float2(-5.0f, 5.0f));
        const uint num_points = 15;
        for (auto i = 0; i < num_points; i++)
        {
            float x = map(0, num_points - 1, -4.5f, 4.5f, i);
            float y = map(0, 1023, camera.bounds().min.y, -1.0f, rand32() % 1024);
            col.add_vertex(float2(x, y)); 
        }
        col.add_vertex(float2(5.0f, 5.0f));
        col.add_vertex(float2(5.0f, -5.0f));
        col.add_vertex(float2(-5.0f, -5.0f));
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
    const uint NUM_BALLS = 8;
    const float BALL_RADIUS = 0.15f;
    const float BALL_VERTS = 16;

    for (auto i = 0; i < NUM_BALLS; i++)
    {
        float posX = map(0, NUM_BALLS - 1, -3.0f, 3.0f, i);
        float posY = map(0, 1023, 4.0f, 1.0f, rand32() % 1024);

        Entity& e = this->scene.new_entity();
        e.add_component<Rigidbody>();
        e.get_component<Rigidbody>().bounciness = 0.9f;
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