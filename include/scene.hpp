#pragma once

class Scene;

#include <vector>
#include <memory>
#include "entity.hpp"
#include "engine.hpp"

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