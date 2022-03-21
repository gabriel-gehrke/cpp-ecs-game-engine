#include "simd.hpp"
#include <cmath>

void float2::normalize()
{
    float l = this->length();
    this->x /= l;
    this->y /= l;
}

float2 float2::normalized() const
{
    float2 v = float2(this->x, this->y);
    v.normalize();
    return v;
}

std::string float2::to_string() const
{
    return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
}