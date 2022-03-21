#pragma once
#include <string>

struct float2
{
    public:
        float2() : x(0), y(0) {}
        float2(float x, float y) : x(x), y(y) {}

        /* Members */

        float x;
        float y;

        /* Const Methods */

        // calculates and returns the length of the vector
        float length() const;
        // calculates and returns the squared length of the vector
        float squared_length() const;
        // returns a normalized copy of the vector
        float2 normalized() const;
        // calculates the dot product of this and another vector
        float dot(const float2& o) const;
        // returns a string representation of the vector
        std::string to_string() const;

        /* Non-Const Methods */

        // normalizes this vector
        void normalize();

        float2 operator+(const float2& o) const {return float2(this->x + o.x, this->y - o.y);}
        float2 operator-(const float2& o) const {return float2(this->x - o.x, this->y - o.y);}
        float2 operator*(float s) const {return float2(this->x * s, this->y * s);}
        float2 operator/(float s) const {return float2(this->x / s, this->y / s);}
        void operator+=(const float2& o) {this->x += o.x; this->y += o.y;}
        void operator-=(const float2& o) {this->x -= o.x; this->y -= o.y;}
        void operator*=(float s) {this->x *= s; this->y *= s;}
        void operator/=(float s) {this->x /= s; this->y /= s;}

        // returns the distance between two points
        static float distance(const float2& a, const float2& b);
        // returns the squared distance between two points
        static float squared_distance(const float2& a, const float2& b);

        // equivalent to float2(0,0)
        static float2 zero() {return float2();};
        // equivalent to float2(1,1)
        static float2 one() {return float2(1, 1);};
};