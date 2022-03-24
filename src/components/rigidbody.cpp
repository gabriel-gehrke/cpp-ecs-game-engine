#include "components/rigidbody.hpp"
#include "collision/collider.hpp"
#include "engine.hpp"

void Rigidbody::update()
{
    if (!this->simulated) return;

    const float dt = this->dt() / 4;

    this->entity.position += this->velocity * dt;
    this->entity.rotation += this->angular_velocity * dt;
    //this->velocity *= drag;
    this->velocity.y += 9.81f * dt;
}


void Rigidbody::on_collision_enter(const Collider& me, const Collider& you, const float2& point, const float2& normal)
{
    const auto frame = this->entity.scene.engine.framecounter;
    if (this->last_updated_frame == frame) return;

    this->last_updated_frame = frame;
    
    if (!you.entity.has_component<Rigidbody>() || !you.entity.get_component<Rigidbody>().simulated)
    {
        // static obstacle (just reflect the velocity vector)
        this->velocity = velocity.reflect(normal) * this->bounciness;
    }
    else
    {
        // dynamic object (more complicated collision response)
        // inspriration: https://fotino.me/2d-rigid-body-collision-response/

        /*
        Rigidbody& rb = you.entity.get_component<Rigidbody>();
        if (this->velocity.dot(rb.velocity) < 0)
        {
            this->velocity = velocity.reflect(normal) * this->bounciness;
        }
        else
        {
            return;
        }
        */

       return;
    }

    this->entity.position += this->velocity * 5 * dt();
}