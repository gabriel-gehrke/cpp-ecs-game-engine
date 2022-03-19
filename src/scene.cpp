#include "scene.hpp"

void Scene::add_entity(Entity* entity)
{
    this->entities.push_back(std::shared_ptr<Entity>(entity));
}