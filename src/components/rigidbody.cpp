#include "components/rigidbody.hpp"

void Rigidbody::update()
{
    if (!this->simulated) return;

    this->entity.position += this->velocity;
    this->velocity *= drag;
}