#include "engine/collision/segment.hpp"
#include <iostream>

static const float EPSILON = 1E-4;

inline static bool is_point_within_segment(const Segment& seg, const float2& point)
{
    float2 ab = seg.ab();
    float2 ap = point - seg.a;
    
    return !(ap.squared_length() > ab.squared_length() || ab.dot(ap) < 0);
}

bool Segment::intersects(const Segment& seg, float2& intersection) const
{
    // inspiration: https://iq.opengenus.org/2d-line-intersection/

    // 1. check if unbounded versions of the lines are intersecting
    const float& x1 = this->a.x;
    const float& y1 = this->a.y;
    const float& x2 = this->b.x;
    const float& y2 = this->b.y;
    const float& x3 = seg.a.x;
    const float& y3 = seg.a.y;
    const float& x4 = seg.b.x;
    const float& y4 = seg.b.y;

    const float x12 = x1 - x2;
    const float x34 = x3 - x4;
    const float y12 = y1 - y2;
    const float y34 = y3 - y4;
    const float c = x12 * y34 - y12 * x34;

    // 1.1: check if lines are (essentially) parallel
    if (std::abs(c) < EPSILON)
        return false;
    
    float a = x1 * y2 - y1 * x2;
    float b = x3 * y4 - y3 * x4;
    float x = (a * x34 - b * x12) / c;
    float y = (a * y34 - b * y12) / c;
    float2 point = float2(x, y);

    // 2. check if point lies on both segments
    if (is_point_within_segment(*this, point) && is_point_within_segment(seg, point))
    {
        intersection = point;
        return true;
    }
    return false;
}