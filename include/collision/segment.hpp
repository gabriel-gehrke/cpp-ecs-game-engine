#pragma once

#include "vectors.hpp"

// a line segment between two points a and b
struct Segment
{
    public:
        Segment(float2 a, float2 b) : a(a), b(b) {}

        float2 a;
        float2 b;

        // vector from a to b
        float2 ab() const {return b - a;}
        // vector from b to a
        float2 ba() const {return a - b;}
        float length() const {return float2::distance(a, b);}
        bool intersects(const Segment& seg, float2& intersection) const;

};