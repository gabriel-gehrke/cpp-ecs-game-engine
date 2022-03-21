#pragma once

class Physics;

#include "collision/collider.hpp"

class Physics
{
    public:

        std::vector<Collider> colliders;
};