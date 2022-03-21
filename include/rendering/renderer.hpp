#pragma once

class Renderer;

#include "component.hpp"
#include "rendering/graphics.hpp"
#include "rendering/bounds.hpp"

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