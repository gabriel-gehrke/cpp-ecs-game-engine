#include "component.hpp"
#include "engine.hpp"
#include "entity.hpp"

float Component::dt() const
{
    return this->entity.scene.engine.dt;
}