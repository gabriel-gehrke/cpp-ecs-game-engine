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

        std::vector<std::shared_ptr<Entity>> entities;
        void add_entity(Entity* entity);
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