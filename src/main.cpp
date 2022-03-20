#include "engine.hpp"
#include "rendering/boxrenderer.hpp"

int main()
{
    auto engine = Engine();

    for (auto i = 0; i < 100; i++)
    {
        // this leaks memeory but I dont care
        Entity* e = new Entity(engine.scene);
        BoxRenderer* r = new BoxRenderer(*e);
        r->size = float2::one() * (rand64() % 500);
        r->entity.position = float2::zero();
    }

    engine.loop();

    return 0;
}