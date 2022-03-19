#pragma once
#include <string>

struct float2
{
    public:
        float2();
        float2(float x, float y);

        float x;
        float y;
        float length();
        float squared_length();
        void normalize();
        float2 normalized();
        std::string to_string();

        float2 operator+(float2 o) const;
        float2 operator-(float2 o) const;
        float2 operator*(float s) const;
        float2 operator/(float s) const;
        void operator+=(float2 o);
        void operator-=(float2 o);
        void operator*=(float s);
        void operator/=(float s);

        static float distance(float2 a, float2 b);
        static float squared_distance(float2 a, float2 b);

        static float2 zero();
        static float2 one();
};