#include "collision/collider.hpp"
#include "engine.hpp"
#include "rendering/graphics.hpp"

void Collider::add_vertex(const float2& v)
{
    this->verts.push_back(v);
    const auto s = this->verts.size();

    if (s > 1)
    {
        this->segments.push_back(Segment(this->verts[s - 2], v));
    }
}

Bounds Collider::bounds() const
{
    return Bounds();
}

void Collider::draw()
{
    const Color green = Color(0, 255, 0);
    const auto size = this->verts.size();

    const auto& center = this->entity.position; 
    this->entity.scene.engine.graphics.draw_circle((int)center.x, (int) center.y, 5, green);

    for (auto i = 0; i < size; i++)
    {
        const auto& v1 = this->verts[i] + center;
        const auto& v2 = this->verts[(i + 1) % size] + center;

        this->entity.scene.engine.graphics.draw_circle((int)v1.x, (int) v1.y, 5, green);
        this->entity.scene.engine.graphics.draw_line((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, green);
    }
}