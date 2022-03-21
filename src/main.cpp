#include "engine.hpp"
#include "rendering/boxrenderer.hpp"
#include "collision/collider.hpp"

int main()
{
    auto engine = Engine();

    // triangle
    Entity* e = new Entity(engine.scene);
    Collider* col = new Collider(*e);
    col->add_vertex(float2(-50, -50));
    col->add_vertex(float2(100, 50));
    col->add_vertex(float2(-50, 50));
    e->position = float2(150, 150);

    // square
    e = new Entity(engine.scene);
    col = new Collider(*e);
    col->add_vertex(float2(-50, -50));
    col->add_vertex(float2(50, -50));
    col->add_vertex(float2(50, 50));
    col->add_vertex(float2(-50, 50));
    e->position = float2(350, 150);

    engine.loop();

    return 0;
}