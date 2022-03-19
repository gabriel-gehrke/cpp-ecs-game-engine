#include "entity.hpp"
#include "random.hpp"

Entity::Entity(Scene& scene) : scene(scene)
{
    scene.add_entity(this);
}

void Entity::add_component(Component* component)
{
    this->components.push_back(std::shared_ptr<Component>(component));
}