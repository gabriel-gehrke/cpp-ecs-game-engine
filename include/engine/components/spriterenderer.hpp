#pragma once

#include "engine/rendering/renderer.hpp"
#include "engine/rendering/sprite.hpp"

class SpriteRenderer: public Renderer
{
    public:
        Sprite* sprite;
        int layer = 0;

        SpriteRenderer(Entity& e) : Renderer(e) {}
        Bounds bounds() const;
        void draw();
};