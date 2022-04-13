#pragma once

#include <vector>
#include <memory>
#include "engine/entity.hpp"

class Engine;

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