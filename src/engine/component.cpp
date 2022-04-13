#include "engine/component.hpp"
#include "engine/engine.hpp"

float Component::dt() const
{
    return this->entity.scene.engine.dt;
}