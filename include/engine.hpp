#pragma once

#include "rendering/graphics.hpp"
#include "entity.hpp"
#include "collision/physics.hpp"
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

        Graphics graphics;
        Physics physics;
        Scene scene;

        void loop();
        void load(Scene& scene);
};