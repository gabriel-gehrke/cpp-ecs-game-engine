#include "simd.hpp"
#include <cmath>

float float2::dot(const float2& o) const
{
    return this->x * o.x + this->y * o.y;
}

float float2::squared_length() const
{
    return dot(*this);
}

float float2::length() const
{
    return std::sqrt(this->squared_length());
}

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

float float2::distance(const float2& a, const float2& b)
{
    return (a - b).length();
}

float float2::squared_distance(const float2& a, const float2& b)
{
    return (a - b).squared_length();
}