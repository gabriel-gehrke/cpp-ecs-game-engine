#pragma once

#include "engine/collision/collider.hpp"

class Physics
{
    public:
        std::vector<Collider*> colliders;

        // calculates a physics step: collisions and movements
        void step();
};