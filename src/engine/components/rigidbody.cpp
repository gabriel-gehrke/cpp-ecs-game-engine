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
    
    // TODO: calc collision depth. the segment class could be expanded to calculate the distance to the accumulated collision point.

    if (!you.entity.has_component<Rigidbody>() || !you.entity.get_component<Rigidbody>().simulated)
    {
        // static obstacle (just reflect the velocity vector)
        this->velocity = velocity.reflect(normal) * this->bounciness;

        this->entity.position += this->velocity * dt();
    }
    else
    {
        // dynamic object (more complicated collision response)
        // inspriration: https://fotino.me/2d-rigid-body-collision-response/

        Rigidbody& rb = you.entity.get_component<Rigidbody>();

        // "undo" collision
        this->entity.position -= this->velocity * dt() * 0.66f;
        rb.entity.position -= rb.velocity * dt() * 0.66f;

        float2 rel_velocity = rb.velocity - this->velocity;
        float vel_along_normal = rel_velocity.dot(normal);

        // don't resolve if velocities are already seperating
        if (vel_along_normal > 0)
            return;

        float restitution = std::min(this->bounciness, rb.bounciness);
        float impulse_scal = -(1.0f + restitution) * vel_along_normal;
        float inv_mass_a = (1.0f / this->mass);
        float inv_mass_b = (1.0f / rb.mass);
        impulse_scal /= inv_mass_a + inv_mass_b;

        float2 impulse = normal * impulse_scal;
        this->velocity -= impulse * inv_mass_a;
        rb.velocity += impulse * inv_mass_b;

        this->entity.position += this->velocity * dt() * 0.66f;
        rb.entity.position += rb.velocity * dt() * 0.66f;

        rb.last_updated_frame = frame;
    }
}