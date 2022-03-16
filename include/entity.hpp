#pragma once
#include "component.hpp"
#include <cstdint>
#include <vector>

class Entity
{


    public:
        Entity();
        Entity(uint64_t id);

        uint64_t id;
        std::vector<Component> components;

        void add_component(Component component);
        
};