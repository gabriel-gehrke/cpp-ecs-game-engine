#pragma once

#include "vectors.hpp"

struct Bounds
{
    public:
        Bounds() {}
        Bounds(float2 min, float2 max) : min(min), max(max) {}

        float2 min;
        float2 max;

        float width() const {return this->max.x - this->min.x;}
        float height() const {return this->max.y - this->min.y;}

        bool intersects(const Bounds& o) const;
        bool contains(const Bounds& o) const;
        bool contains(const float2& p) const;

        static Bounds from_pos_and_size(const float2& pos, const float2& size);
};