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
        inline float2 ab() const {return b - a;}
        // vector from b to a
        inline float2 ba() const {return a - b;}

        // returns the length of the line segment
        inline float length() const 
        {
            return float2::distance(a, b);
        }

        // checks if the line segments intersect. the intersection reference is only overwritten if the segments intersect.
        bool intersects(const Segment& seg, float2& intersection) const;

        // calculates and returns the minimal distance of a point on the segment to the given point
        float distance(const float2& e) const
        {
            const float2 AB = ab();
            const float2 BE = e - b;
            const float2 AE = e - a;

            if (AB.dot(BE) > 0)
            {
                // point lies beyond b
                return (e - b).length();
            }
            else if (AB.dot(AE) < 0)
            {
                // point lies before a
                return (e - a).length();
            }
            else
            {
                // is perpendicular to line
                return std::abs(AB.cross(AE)) / length();
            }
        }

};