#include "simd.hpp"
#include <cmath>

float sqrlength2(float2& vec)
{
    float x = vec[0];
    float y = vec[1];

    return x*x + y*y;
}

float length2(float2& vec)
{
    return sqrtf32(sqrlength2(vec));
}

float sqrlength3(float4& vec)
{
    float x = vec[0];
    float y = vec[1];
    float z = vec[2];
    return x*x + y*y + z*z;
}

float length3(float4& vec)
{
    return sqrtf32(sqrlength3(vec));
}