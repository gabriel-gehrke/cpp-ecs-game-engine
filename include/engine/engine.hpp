#pragma once

#include "engine/rendering/graphics.hpp"
#include "engine/collision/physics.hpp"
#include "engine/camera.hpp"
#include "engine/scene.hpp"

class Engine
{

    public:
        Engine();

        Physics physics;
        Scene scene;
        Camera camera;

        uint32_t target_fps = 60;
        uint64_t framecounter = 1;
        float dt = 1 / target_fps;

        void loop();
        void load(Scene& scene);
};