#pragma once

inline float map(float amin, float amax, float bmin, float bmax, float value)
{
    return (((value - amin) * (bmax-bmin)) / (amax-amin)) + bmin;
}