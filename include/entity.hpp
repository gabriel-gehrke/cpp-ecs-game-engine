#pragma once
#include <cstdint>
#pragma once

class Component;
class Entity;

#include <vector>
#include <memory>
#include "simd.hpp"
#include "random.hpp"
#include "engine.hpp"

class Entity
{
    public:

        Entity(Scene& scene);
    
        uint64_t id = rand64();
        float2 position = float2::zero();
        Scene& scene;
        std::vector<std::shared_ptr<Component>> components;

        void add_component(Component* component);

};

class Component
{
    public:
        Component(Entity& entity) : entity(entity)
        {
            entity.add_component(this);
        }
        virtual void update() = 0;

        Entity& entity;
        
};