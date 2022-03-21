#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include "simd.hpp"
#include "random.hpp"

class Engine;
class Scene;
class Component;

class Entity
{
    public:

        Entity(Scene& scene);
    
        uuid id = randid();
        float2 position = float2::zero();
        Scene& scene;
        std::vector<std::shared_ptr<Component>> components;

        void add_component(Component* component);

};