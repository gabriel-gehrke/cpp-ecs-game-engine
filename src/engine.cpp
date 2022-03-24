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
        e.get_component<Rigidbody>().bounciness = 0.99f;
        e.position = float2(1280 / 2, 100);
    }
    */
    
    // circles
    const uint NUM_BALLS = 1;
    const float BALL_RADIUS = 50;
    const float BALL_VERTS = 20;

    for (auto i = 0; i < NUM_BALLS; i++)
    {
        float posX = (1280 / (NUM_BALLS + 2)) * (i + 1);
        float posY = randrange(100, 300);

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

        SDL_Delay(10);  // setting some Delay
        this->graphics.clear();

        physics.step();

        const float speed = 3;

        /*
        if (event.type == SDL_KEYDOWN)
        {
            Rigidbody& rb = e.get_component<Rigidbody>();
            auto code = event.key.keysym.scancode;

            rb.velocity.y = -speed * (code == SDL_SCANCODE_W) + speed * (code == SDL_SCANCODE_S);
            rb.velocity.x = -speed * (code == SDL_SCANCODE_A) + speed * (code == SDL_SCANCODE_D);
        }
        */

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