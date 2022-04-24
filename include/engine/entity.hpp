#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <iostream>
#include <assert.h>

#include "engine/vectors.hpp"
#include "engine/random.hpp"
#include "engine/component.hpp"

class Engine;
class Scene;
class Component;

static const inline float DEG_TO_RAD = ((float)M_PIf32x / 180.0f);

class Entity
{
    public:

        Entity(Scene& scene) : scene(scene) {}
    
        uuid id = randid();
        float2 position = float2::zero();
        float2 scale = float2::one();
        float rotation = 0;
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

        // returns the upwards direction of the object
        float2 up() const
        {
            const float radians = this->rotation * DEG_TO_RAD;
            return float2(std::sin(radians), std::cos(radians));
        }

        float2 right() const
        {
            const float radians = (this->rotation + 90.0f) * DEG_TO_RAD;
            return float2(std::sin(radians), std::cos(radians));
        }

        void set_up(const float2& v)
        {
            this->rotation = std::atan2(v.x, v.y) / DEG_TO_RAD;
        }

        void set_right(const float2& v)
        {

        }

        // checks if a component of the specified type is attached to the entity
        template<typename T> bool has_component() const
        {
            static_assert(std::is_base_of<Component, T>(), "The component class to check must derive from Component!");
            return this->component_map.end() != this->component_map.find(std::type_index(typeid(T)));
        }

        // creates and attaches a component of the type to this entity. (more than one component per type is not allowed.)
        template<typename T> T& add_component()
        {
            static_assert(std::is_base_of<Component, T>(), "The component class to add must derive from Component!");

            if (this->has_component<T>())
            {
                std::cout << "Warn: Entity " << this << " already has Component " << typeid(T).name() << " attached!" << std::endl;
                return this->get_component<T>();
            }

            T* t = new T(*this);
            this->component_map.emplace(std::type_index(typeid(T)), t);

            static_cast<Component*>(t)->awake();
            return *t;
        }

        template <typename T> T& get_component() const
        {
            static_assert(std::is_base_of<Component, T>(), "The component class to retrieve must derive from Component!");
            assert(this->has_component<T>());
            T& component = (T&) *this->component_map.at(std::type_index(typeid(T)));
            return component;
        }

    private:
        std::unordered_map<std::type_index, Component*> component_map;
};