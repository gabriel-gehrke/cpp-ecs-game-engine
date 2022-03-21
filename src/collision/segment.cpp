#include "collision/segment.hpp"

static const float EPSILON = 1E-6;

bool Segment::intersects(const Segment& seg, float2& intersection) const
{
    // inspiration: https://iq.opengenus.org/2d-line-intersection/

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

    // check if lines are parallel
    if (std::abs(c) < EPSILON)
        return false;
    
    float a = x1 * y2 - y1 * x2;
    float b = x3 * y4 - y3 * x4;
    float x = (a * x34 - b * x12) / c;
    float y = (a * y34 - b * y12) / c;
    float2 p(x, y);

    // check whether (x, y) is on this segment (and therefore on both lines)
    float2 d1 = this->ab();
    float2 d2 = p - this->a;

    // 1.: check if both vectors face same direction
    if (d1.dot(d2) > 1.0f - EPSILON && d1.squared_length() >= d2.squared_length())
    {
        intersection = p;
        return true;
    }

    return false;
}