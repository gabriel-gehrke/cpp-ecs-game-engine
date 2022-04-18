#include "engine/collision/collider.hpp"
#include "engine/collision/segment.hpp"
#include "engine/engine.hpp"
#include "engine/rendering/graphics.hpp"

Collider::Collider(Entity& entity) : Renderer(entity)
{
    entity.scene.engine.physics.colliders.push_back(this);
};

void Collider::add_vertex(const float2& v)
{
    this->verts.push_back(v);
}

inline float2 Collider::translate_point(float2 vert) const
{
    // apply scale
    const auto& scale = this->entity.scale;
    vert.x *= scale.x;
    vert.y *= scale.y;

    // apply entity position and rotation
    const auto& center = this->entity.position;
    const auto& rotation = this->entity.rotation;
    return (vert + center).rotate_around(center, rotation);
}

Segment Collider::segment(uint index) const
{
    const auto size = num_segments();
    const auto p1 = translate_point(this->verts[index % size]);
    const auto p2 = translate_point(this->verts[(index + 1) % size]);
    return Segment(p1, p2);
}

Bounds Collider::bounds() const
{
    return Bounds();
}


void Collider::draw()
{
    const auto size = this->verts.size();

    // only for drawing middle point, center is not needed
    {
        const auto& center = translate_point(float2(0, 0)); 
        Graphics::draw_circle((int)center.x, (int) center.y, 5, this->color);
    }

    const auto& cam = this->entity.scene.engine.camera;
    for (uint i = 0; i < size; i++)
    {
        const int2 v1 = cam.world_to_screenpos(translate_point(this->verts[i]));
        const int2 v2 = cam.world_to_screenpos(translate_point(this->verts[(i + 1) % size]));

        Graphics::draw_line(v1.x, v1.y, v2.x, v2.y, this->color);
    }

    this->color = Color(0, 255, 0);
}

bool Collider::collides_with(const Collider& c, float2& point, float2& normal) const
{
    point.x = 0;
    point.y = 0;
    uint collisions = 0;
    float2 points[this->num_segments() * c.num_segments()];
    float2 avg = float2::zero();

    const auto l = num_segments();
    for (uint i = 0; i < l; i++)
    {
        const auto k = c.num_segments();
        for (uint j = 0; j < k; j++)
        {
            const auto s1 = this->segment(i);
            const auto s2 = c.segment(j);

            float2 p;
            if (s1.intersects(s2, p))
            {
                Graphics::draw_circle((int)p.x, (int)p.y, 5, Color(0,0,255));
                points[collisions++] = p;
                avg += p;
            }
        }
    }

    if (collisions < 2) return false;
    avg /= (float)collisions;

    // linear regression over all collision points
    float d = 0;
    float e = 0;
    for (uint i = 0; i < collisions; i++)
    {
        float f = points[i].x - avg.x; 

        d += f * (points[i].y - avg.y);
        e += f * f;
    }

    if (std::abs(e) < 1E-5)
    {
        // infinite slope -> vertical collision line -> hoizontal normal
        normal = float2(1, 0);
    }
    else
    {
        // normal = orthogonal to slope vector
        normal = float2(1, d / e).orthogonal().normalized();
    }
    point = avg;

    return true;
}

void Collider::on_collision_enter(const Collider& me, const Collider& you, const float2& p, const float2& normal)
{
    const auto& cam = this->entity.scene.engine.camera;

    // draw the collision point
    Graphics::draw_circle(cam.world_to_screenpos(p), 5, Color(255,255,0));

    // calculate and visualize the collision normal
    const float len = 0.1f;
    float2 l = normal * len;

    int2 lp1 = cam.world_to_screenpos(p + l);
    int2 lp2 = cam.world_to_screenpos(p - l);

    Graphics::draw_line(lp1, lp2, Color(255, 0, 255));

    this->color = Color(255, 0, 0);
}