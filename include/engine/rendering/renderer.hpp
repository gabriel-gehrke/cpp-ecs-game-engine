#pragma once

class Renderer;

#include "engine/component.hpp"
#include "engine/rendering/graphics.hpp"
#include "engine/rendering/bounds.hpp"

class Renderer : public Component
{
    public:
        Renderer(Entity& e) : Component(e)
        {
            
        }

        void update();

        virtual Bounds bounds() const = 0;
        virtual void draw() = 0;
};