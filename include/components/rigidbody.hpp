#pragma once

#include "component.hpp"
#include "simd.hpp"

class Rigidbody : public Component
{
    public:
        Rigidbody(Entity& e) : Component(e) {}

        float2 velocity;
        float drag = 1;
        float bounciness = 0.8f;
        bool simulated = true;

        void update() override;
        void on_collision_enter(const Collider& me, const Collider& you, const float2& point, const float2& normal) override;
};