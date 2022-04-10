#pragma once

#include "rendering/renderer.hpp"
#include "rendering/sprite.hpp"

class SpriteRenderer: public Renderer
{
    public:
        Sprite sprite;

        SpriteRenderer(Entity& e) : Renderer(e) {}
        Bounds bounds() const;
        void draw();
};