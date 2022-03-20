#pragma once
#include <string>

struct float2
{
    public:
        float2();
        float2(float x, float y);

        float x;
        float y;

        void normalize();

        float dot(const float2& o) const;
        float length() const;
        float squared_length() const;
        float2 normalized() const;
        
        std::string to_string() const;

        float2 operator+(const float2& o) const;
        float2 operator-(const float2& o) const;
        float2 operator*(float s) const;
        float2 operator/(float s) const;
        void operator+=(const float2& o);
        void operator-=(const float2& o);
        void operator*=(float s);
        void operator/=(float s);

        static float distance(const float2& a, const float2& b);
        static float squared_distance(const float2& a, const float2& b);

        static float2 zero();
        static float2 one();
};