#pragma once

#include "engine/rendering/graphics.hpp"
#include "engine/rendering/renderer.hpp"
#include "engine/rendering/bounds.hpp"
#include "engine/collision/segment.hpp"

#include <vector>

class Collider : public Renderer
{
    public:
        Collider(Entity& entity);

        std::vector<float2> verts;

        void add_vertex(const float2& v);
        bool collides_with(const Collider& c, float2& point, float2& normal) const;
        Bounds bounds() const;
        void draw();

        uint num_segments() const {return this->verts.size();}

        // returns the line segment between the point at the index and the next point
        Segment segment(uint index) const;

        void on_collision_enter(const Collider& me, const Collider& you, const float2& point, const float2& normal) override;
    
    private:
        Color color = Color(0, 255, 0);

        float2 translate_point(float2 vert) const;
};
