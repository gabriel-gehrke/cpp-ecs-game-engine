#include "simd.hpp"
#include <cmath>

float2::float2() : float2(0, 0)
{
}

float2::float2(float x, float y)
{
    this->x = x;
    this->y = y;
}

float float2::squared_length()
{
    return this->x * this->x + this->y * this->y;
}

float float2::length()
{
    return sqrtf32(this->squared_length());
}

void float2::normalize()
{
    float l = this->length();
    this->x /= l;
    this->y /= l;
}

float2 float2::normalized()
{
    float2 v = float2(this->x, this->y);
    v.normalize();
    return v;
}

std::string float2::to_string()
{
    return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
}

float2 float2::operator+(float2 o)
{
    return float2(this->x + o.x, this->y + o.y);
}

float2 float2::operator-(float2 o)
{
    return float2(this->x - o.x, this->y - o.y);
}

float2 float2::operator*(float s)
{
    return float2(this->x * s, this->y * s);
}

float2 float2::operator/(float s)
{
    return float2(this->x / s, this->y / s);
}

void float2::operator+=(float2 o)
{
    this->x += o.x;
    this->y += o.y;
}

void float2::operator-=(float2 o)
{
    this->x -= o.x;
    this->y -= o.y;
}

void float2::operator*=(float s)
{
    this->x *= s;
    this->y *= s;
}

void float2::operator/=(float s)
{
    this->x /= s;
    this->y /= s;
}

float float2::distance(float2 a, float2 b)
{
    return (a - b).length();
}

float float2::squared_distance(float2 a, float2 b)
{
    return (a - b).squared_length();
}