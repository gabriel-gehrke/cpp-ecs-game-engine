#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <iostream>
#include <assert.h>

#include "simd.hpp"
#include "random.hpp"

class Engine;
class Scene;
class Component;


class Entity
{
    public:

        Entity(Scene& scene) : scene(scene) {}
    
        uuid id = randid();
        float2 position = float2::zero();
        float rotation;
        Scene& scene;


        bool operator==(const Entity& other) const
        {
            return this->id == other.id;
        }

        inline auto begin() const noexcept
        {
            return this->component_map.begin();
        }

        inline auto end() const noexcept
        {
            return this->component_map.end();
        }

        // checks if a component of the specified type is attached to the entity
        template<typename T> inline bool has_component() const
        {
            static_assert(std::is_base_of<Component, T>(), "The component class must derive from Component!");
            return this->component_map.find(std::type_index(typeid(T))) != this->component_map.end();
        }

        // creates and attaches a component of the type to this entity. (note: duplicate component types are not allowed.)
        template<typename T> inline T& add_component()
        {
            static_assert(std::is_base_of<Component, T>(), "The component class must derive from Component!");

            if (this->has_component<T>())
            {
                std::cout << "Entity " << this << " already has Component " << typeid(T).name() << " attached!" << std::endl;
                return this->get_component<T>();
            }

            T* t = new T(*this);
            this->component_map.emplace(std::type_index(typeid(T)), std::shared_ptr<T>(t));

            return *t;
        }

        template <typename T> T& get_component() const
        {
            static_assert(std::is_base_of<Component, T>(), "The component class must derive from Component!");
            assert(this->has_component<T>());
            T& component = (T&) *this->component_map.at(std::type_index(typeid(T)));
            return component;
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> component_map;
};