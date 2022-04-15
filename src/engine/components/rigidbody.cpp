#include "engine/components/rigidbody.hpp"
#include "engine/collision/collider.hpp"
#include "engine/engine.hpp"

void Rigidbody::update()
{
    if (!this->simulated) return;

    this->entity.position += this->velocity * dt();
    this->entity.rotation += this->angular_velocity * dt();
    //this->velocity *= drag;
    this->velocity.y -= 9.81f * dt();
}


void Rigidbody::on_collision_enter(const Collider& me, const Collider& you, const float2& point, const float2& normal)
{
    const auto frame = this->entity.scene.engine.framecounter;
    if (this->last_updated_frame == frame) return;

    this->last_updated_frame = frame;
    
    // determine collision depth

    float collision_depth = std::numeric_limits<float>::max();
    const auto n = me.num_segments();
    const auto m = you.num_segments();

    for (auto i = 0; i < n; i++)
    {
        const auto& seg = me.segment(i);
        collision_depth = std::min(collision_depth, seg.distance(point));
    }
    for (auto i = 0; i < m; i++)
    {
        const auto& seg = you.segment(i);
        collision_depth = std::min(collision_depth, seg.distance(point));
    }

    // react to collision

    if (!you.entity.has_component<Rigidbody>() || !you.entity.get_component<Rigidbody>().simulated)
    {
        // static obstacle (just reflect the velocity vector)

        me.entity.position -= this->velocity * dt();
        this->velocity = velocity.reflect(normal) * this->bounciness;
    }
    else
    {
        // dynamic object (more complicated collision response)
        // inspriration: https://fotino.me/2d-rigid-body-collision-response/

        Rigidbody& rb = you.entity.get_component<Rigidbody>();

        if (rb.velocity.dot(normal) > 0)
        {
            me.entity.position += normal * collision_depth;
            rb.entity.position -= normal * collision_depth; 
        }
        else
        {
            me.entity.position -= normal * collision_depth;
            rb.entity.position += normal * collision_depth;
        }

        float2 rel_velocity = rb.velocity - this->velocity;
        float vel_along_normal = rel_velocity.dot(normal);

        // don't resolve if velocities are already seperating
        if (vel_along_normal < 0)
        {
            float restitution = std::min(this->bounciness, rb.bounciness);
            float impulse_scal = -(1.0f + restitution) * vel_along_normal;
            float inv_mass_a = (1.0f / this->mass);
            float inv_mass_b = (1.0f / rb.mass);
            impulse_scal /= inv_mass_a + inv_mass_b;

            float2 impulse = normal * impulse_scal;
            this->velocity -= impulse * inv_mass_a;
            rb.velocity += impulse * inv_mass_b;

            rb.last_updated_frame = frame;
        }
    }
}