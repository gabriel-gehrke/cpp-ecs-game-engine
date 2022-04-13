#include "engine/engine.hpp"
#include "engine/rendering/boxrenderer.hpp"
#include "engine/collision/collider.hpp"

int main()
{
    auto engine = Engine();

    engine.loop();

    return 0;
}