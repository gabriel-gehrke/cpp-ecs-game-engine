#include "components/rigidbody.hpp"

void Rigidbody::update()
{
    if (!this->simulated) return;

    this->entity.position += this->velocity;
    this->velocity *= drag;
    this->velocity.y += 9.81f / 120;
}

void Rigidbody::on_collision_enter(const Collider& me, const Collider& you, const float2& point, const float2& normal)
{
    this->entity.position -= this->velocity;
    this->velocity = velocity.reflect(normal) * this->bounciness;
    this->entity.position += this->velocity * 0.5f;
}