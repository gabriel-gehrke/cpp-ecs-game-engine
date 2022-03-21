#pragma once

class Entity;
class Collider;
class Component;

#include "entity.hpp"

class Component
{
    public:
        Component(Entity& entity) : entity(entity)
        {
            entity.add_component(this);
        }


        virtual void update() = 0;

        // can be overriden to model behavior on entities with colliders attached
        void on_collision_enter(const Collider& own_collider, const Collider& other_collider, float2 collision_point) {}

        Entity& entity;
        
};