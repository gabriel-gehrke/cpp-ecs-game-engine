#pragma once

#include "rendering/renderer.hpp"

class BoxRenderer : public Renderer
{
    public:
        float2 size;

        Bounds bounds() const;
        void draw();
};