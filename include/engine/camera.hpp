#pragma once

#include "engine/vectors.hpp"
#include "engine/algebra.hpp"
#include "engine/rendering/bounds.hpp"
#include "engine/rendering/graphics.hpp"

// an implementation of an orthographic camera. its field of view (fov) is adjustable by its "width" variable.
class Camera
{
    public:
        Camera(float w) : width(w) {};

        // world width that fits on screen (similar to fov in 3D)
        float width;

        // position in world space (center)
        float2 position;

        
        inline int2 world_to_screenpos(float x, float y) const {return world_to_screenpos(float2(x, y));}
        inline int2 world_to_screenpos(float2 point) const
        {
            const int2 screensize = Graphics::get_size();
            const float height = ((float)screensize.y / (float)screensize.x) * width;

            // account for camera's position
            point -= this->position;

            // map point to screen space using linear mapping
            const float2 hsize = float2(width, height) * 0.5f;
            const int x = (int) map(-hsize.x, hsize.x, 0, screensize.x, point.x);
            const int y = (int) map(-hsize.y, hsize.y, screensize.y, 0, point.y);
            
            return int2(x, y);
        }

        inline float2 screen_to_worldpos(int2 pos) const {return screen_to_worldpos(pos.x, pos.y);}
        inline float2 screen_to_worldpos(int x, int y) const
        {
            const int2 screensize = Graphics::get_size();
            const float height = ((float)screensize.y / (float)screensize.x) * width;
            const float2 hsize = float2(width, height) * 0.5f;

            const float2 minp = this->position - hsize;
            const float2 maxp = this->position + hsize;

            const float wpx = map(0, screensize.x, minp.x, maxp.x, x);
            const float wpy = map(0, screensize.y, maxp.y, minp.y, y);

            return float2(wpx, wpy);
        }

        // calculates the world bounds of the camera
        inline Bounds bounds() const
        {
            const int2 screensize = Graphics::get_size();
            const float height = ((float)screensize.y / (float)screensize.x) * width;
            const float2 hsize = float2(width, height) * 0.5f;

            return Bounds(this->position - hsize, this->position + hsize);
        }

        
};

