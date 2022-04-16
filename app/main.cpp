#include "engine/engine.hpp"
#include "engine/rendering/sprite.hpp"
#include "engine/collision/collider.hpp"
#include "engine/components/rigidbody.hpp"
#include "engine/components/spriterenderer.hpp"
#include <SDL.h>

int main()
{
    auto engine = Engine();
    engine.camera = Camera(10.0f);

    // add ground
    {
        Entity& e = engine.scene.new_entity();
        Collider& col = e.add_component<Collider>();
        col.add_vertex(float2(-5.0f, 5.0f));
        const uint num_points = 15;
        for (auto i = 0; i < num_points; i++)
        {
            float x = map(0, num_points - 1, -4.5f, 4.5f, i);
            float y = map(0, 1023, engine.camera.bounds().min.y, -1.0f, rand32() % 1024);
            col.add_vertex(float2(x, y)); 
        }
        col.add_vertex(float2(5.0f, 5.0f));
        col.add_vertex(float2(5.0f, -5.0f));
        col.add_vertex(float2(-5.0f, -5.0f));
    }

    // balls
    const uint NUM_BALLS = 12;
    const float BALL_RADIUS = 0.1f;
    const float BALL_VERTS = 8;

    for (auto i = 0; i < NUM_BALLS; i++)
    {
        float posX = map(0, NUM_BALLS - 1, -3.0f, 3.0f, i);
        float posY = map(0, 1023, 4.0f, 1.0f, rand32() % 1024);

        Entity& e = engine.scene.new_entity();
        e.scale = float2(BALL_RADIUS, BALL_RADIUS) * 2.0f;
        e.add_component<Rigidbody>();
        e.get_component<Rigidbody>().bounciness = 0.8f;
        e.position = float2(posX, posY);

        Collider& col = e.add_component<Collider>();

        for (auto i = 0; i < BALL_VERTS; i++)
        {
            float angle = ((M_PI * 2) / BALL_VERTS) * i;
            float x = std::sin(angle);
            float y = std::cos(angle);
            col.add_vertex(float2(x, y));
        }
    }

   // squares

    // hand over control to engine
    engine.loop();

    return 0;
}