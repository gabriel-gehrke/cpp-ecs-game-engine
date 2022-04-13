#pragma once

#include "engine/collision/collider.hpp"
#include <memory>

class Physics
{
    public:
        std::vector<std::shared_ptr<Collider>> colliders;

        // calculates a physics step: collisions and movements
        void step() const;
};