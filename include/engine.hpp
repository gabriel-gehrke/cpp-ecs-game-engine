#pragma once

#include "rendering/graphics.hpp"
#include "entity.hpp"
#include "collision/physics.hpp"
#include "camera.hpp"
#include <vector>
#include <memory>

class Scene
{
    public:
        Scene(Engine& engine) : engine(engine)
        {
            
        }

        Engine& engine;

        std::vector<std::unique_ptr<Entity>> entities;
        Entity& new_entity();
};

class Engine
{

    public:
        Engine();

        Physics physics;
        Camera camera;
        Scene scene;

        uint32_t target_fps = 60;
        uint64_t framecounter = 1;
        float dt = 1 / target_fps;

        void loop();
        void load(Scene& scene);
};