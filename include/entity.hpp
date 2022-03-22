#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include "simd.hpp"
#include "random.hpp"
#include <type_traits>

class Engine;
class Scene;
class Component;

class Entity
{
    public:

        Entity(Scene& scene) : scene(scene) {}
    
        uuid id = randid();
        float2 position = float2::zero();
        Scene& scene;
        std::vector<std::unique_ptr<Component>> components;

        // creates and adds a component of the type to this entity
        template<typename T> T& add_component()
        {
            static_assert(std::is_base_of<Component, T>(), "The component class must derive from Component!");

            T* t = new T(*this);
            this->components.push_back(std::unique_ptr<Component>(t));
            return *t;
        }

};