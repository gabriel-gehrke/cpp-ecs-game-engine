#pragma once

#include <vector>
#include "engine/entity.hpp"

class Engine;

class Scene
{
    public:
        Scene(Engine& engine) : engine(engine)
        {
            
        }

        Engine& engine;

        std::vector<Entity*> entities;
        Entity& new_entity();
};