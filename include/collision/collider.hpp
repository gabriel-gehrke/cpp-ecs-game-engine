#pragma once

#include "rendering/graphics.hpp"
#include "rendering/renderer.hpp"
#include "rendering/bounds.hpp"
#include "collision/segment.hpp"

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
};
