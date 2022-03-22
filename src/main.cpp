#include "engine.hpp"
#include "rendering/boxrenderer.hpp"
#include "collision/collider.hpp"

int main()
{
    auto engine = Engine();

    engine.loop();

    return 0;
}