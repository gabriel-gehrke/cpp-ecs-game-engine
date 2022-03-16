#include "entity.hpp"
#include "random.hpp"

Entity::Entity() : Entity(rand64())
{
    
}

Entity::Entity(uint64_t id)
{
    this->id = id;
    this->components = std::vector<Component>();
}

void Entity::add_component(Component component)
{
    this->components.push_back(component);
}