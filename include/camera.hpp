#pragma once

#include "vectors.hpp"
#include "bounds.hpp"
#include "graphics.hpp"

class Camera
{
    public:
        Camera(float w) : width(w) {};

        // world width that should fit on screen
        float width;

        // position in world space (center)
        float2 position;

        
        inline int2 world_to_screenpos(float x, float y) const {return world_to_screenpos(float2(x, y));}
        inline int2 world_to_screenpos(float2 point) const
        {
            const auto screensize = Graphics::get_size();
            const float height = ((float)screensize.y / (float)screensize.x) * width;

            // account for camera's position and size
            point -= this->position + float2(width / 2, height / 2);

            // get "percentage" along each axis
            const int x = (int) ((point.x / width) * screensize.x);
            const int y = (int) ((point.y / height) * screensize.y);
            return int2(x, y);
        }

        inline float2 screen_to_worldpos(int2 pos) const {return screen_to_worldpos(pos.x, pos.y);}
        inline float2 screen_to_worldpos(int x, int y) const
        {
            return float2((float)x, (float)y);
        }

        inline float2 size() const
        {
            const auto screensize = Graphics::get_size();
            const float height = ((float)screensize.y / (float)screensize.x) * width;
            return float2(width, height);
        }

        // calculates the world bounds of the camera
        inline Bounds bounds() const
        {
            return Bounds(screen_to_worldpos(0, 0), screen_to_worldpos(Graphics::get_size()));
        }

        
};

