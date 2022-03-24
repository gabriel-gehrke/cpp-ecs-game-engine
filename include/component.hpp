#pragma once

class Entity;
class Collider;
class Component;

#include "entity.hpp"

class Component
{
    public:
        Component(Entity& entity) : entity(entity) {}


        virtual void update() = 0;

        // can be overriden to model behavior on entities with colliders attached
        virtual void on_collision_enter(const Collider& own_collider, const Collider& other_collider, const float2& collision_point, const float2& normal)
        {
            
        }

        Entity& entity;
    protected:
        float dt() const;
        
};