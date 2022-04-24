#pragma once

#include "engine/entity.hpp"

class TileRenderer : public Component
{
    public:
        TileRenderer(Entity& e) : Component(e)
        {
            void update();
        }

};