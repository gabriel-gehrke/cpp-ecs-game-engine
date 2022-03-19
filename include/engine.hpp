#pragma once

#include "rendering/graphics.hpp"

class Engine
{

    public:
        Engine() : graphics(Graphics(1280, 720))
        {

        }

        Graphics graphics;
};