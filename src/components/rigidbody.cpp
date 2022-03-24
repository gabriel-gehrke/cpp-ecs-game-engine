#include "components/rigidbody.hpp"
#include "collision/collider.hpp"

void Rigidbody::update()
{
    if (!this->simulated) return;

    this->entity.position += this->velocity;
    this->velocity *= drag;
    this->velocity.y += 9.81f / 120;
}

void Rigidbody::on_collision_enter(const Collider& me, const Collider& you, const float2& point, const float2& normal)
{
    
    if (!you.entity.has_component<Rigidbody>() || !you.entity.get_component<Rigidbody>().simulated)
    {
        // static obstacle (just reflect the velocity vector)
        this->velocity = velocity.reflect(normal) * this->bounciness;
    }
    else
    {
        // dynamic object (more complicated collision response)
        // inspriration: https://fotino.me/2d-rigid-body-collision-response/

        Rigidbody& rb = you.entity.get_component<Rigidbody>();
        
        
    }

    this->entity.position += this->velocity * 0.66f;
}