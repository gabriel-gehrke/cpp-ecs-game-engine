#pragma once

#include "simd.hpp"

struct Bounds
{
    public:
        Bounds();
        Bounds(float2 min, float2 max);

        float2 min;
        float2 max;

        float width() const;
        float height() const;

        bool intersects(const Bounds& o) const;

        static Bounds from_pos_and_size(const float2& pos, const float2& size);
};