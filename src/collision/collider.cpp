#include "collision/collider.hpp"
#include "collision/segment.hpp"
#include "engine.hpp"
#include "rendering/graphics.hpp"

Collider::Collider(Entity& entity) : Renderer(entity)
{
    entity.scene.engine.physics.colliders.push_back(std::shared_ptr<Collider>(this));
};

void Collider::add_vertex(const float2& v)
{
    this->verts.push_back(v);
}

Segment Collider::segment(uint index) const
{
    const auto size = num_segments();
    const auto& p1 = this->verts[index % size];
    const auto& p2 = this->verts[(index + 1) % size];
    const auto& center = this->entity.position;
    return Segment(p1 + center, p2 + center);
}

Bounds Collider::bounds() const
{
    return Bounds();
}

void Collider::draw()
{
    const auto size = this->verts.size();

    const auto& center = this->entity.position; 
    this->entity.scene.engine.graphics.draw_circle((int)center.x, (int) center.y, 5, this->color);

    for (auto i = 0; i < size; i++)
    {
        const auto& v1 = this->verts[i] + center;
        const auto& v2 = this->verts[(i + 1) % size] + center;

        this->entity.scene.engine.graphics.draw_circle((int)v1.x, (int) v1.y, 5, this->color);
        this->entity.scene.engine.graphics.draw_line((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, this->color);
    }

    this->color = Color(0, 255, 0);
}

bool Collider::collides_with(const Collider& c, float2& point) const
{
    point.x = 0;
    point.y = 0;
    uint collisions = 0;

    const auto l = num_segments();
    for (auto i = 0; i < l; i++)
    {
        const auto k = c.num_segments();
        for (auto j = 0; j < k; j++)
        {
            const auto s1 = this->segment(i);
            const auto s2 = c.segment(j);

            float2 p;
            if (s1.intersects(s2, p))
            {
                this->entity.scene.engine.graphics.draw_circle((int)p.x, (int)p.y, 5, Color(0,0,255));
                point += p;
                collisions++;
            }
        }
    }

    if (collisions == 0) return false;

    point /= (float) collisions;
    return true;
}

void Collider::on_collision_enter(const Collider& me, const Collider& you, const float2& point)
{
    this->color = Color(255, 0, 0);
}