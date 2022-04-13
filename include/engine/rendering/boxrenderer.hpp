#pragma once

#include "engine/rendering/renderer.hpp"

class BoxRenderer : public Renderer
{
    public:
        BoxRenderer(Entity& e) : Renderer(e)
        {
            
        }

        float2 size;

        Bounds bounds() const;
        void draw();
};