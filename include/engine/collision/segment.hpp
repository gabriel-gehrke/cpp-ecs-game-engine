#pragma once

#include "engine/vectors.hpp"

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

        // returns the length of the line segment
        float length() const {return float2::distance(a, b);}

        // checks if the line segments intersect. the intersection reference is only overwritten if the segments intersect.
        bool intersects(const Segment& seg, float2& intersection) const;

};