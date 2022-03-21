#pragma once

class Collider;

#include "rendering/renderer.hpp"
#include "collision/segment.hpp"

class Collider : public Renderer
{
    public:
        Collider(Entity& entity) : Renderer(entity) {};

        std::vector<float2> verts;
        std::vector<Segment> segments;

        void add_vertex(const float2& v);
        Bounds bounds() const;
        void draw();
};
