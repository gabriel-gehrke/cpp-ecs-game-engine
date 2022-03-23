#pragma once

#include "component.hpp"
#include "simd.hpp"

class Rigidbody : public Component
{
    public:
        Rigidbody(Entity& e) : Component(e), velocity(float2::one()) {}

        float2 velocity;
        float drag = 0.99f;
        bool simulated = true;

        void update() override;
};