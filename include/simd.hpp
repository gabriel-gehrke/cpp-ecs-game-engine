#pragma once
#include <string>
#include <cmath>

struct float2
{
    public:
        float2() : x(0), y(0) {}
        float2(float x, float y) : x(x), y(y) {}

        /* MEMBERS */

        float x;
        float y;

        /* CONST METHODS */

        // calculates and returns the length of the vector
        float length() const {return std::sqrt(this->squared_length());}
        // calculates and returns the squared length of the vector
        float squared_length() const {return this->dot(*this);}
        // returns a normalized copy of the vector
        float2 normalized() const;
        // calculates the dot product of this and another vector
        float dot(const float2& o) const {return this->x * o.x + this->y * o.y;}
        // calculates the "unofficial" 2D-cross-product vx * wy − vy * wx.
        float cross(const float2& o) const {return this->x * o.y - this->y * o.x;}
        // returns a string representation of the vector
        std::string to_string() const;

        /* NON-CONST METHODS */

        // normalizes this vector
        void normalize();

        /* OPERATORS */

        float2 operator+(const float2& o) const {return float2(this->x + o.x, this->y + o.y);}
        float2 operator-(const float2& o) const {return float2(this->x - o.x, this->y - o.y);}
        float2 operator*(float s) const {return float2(this->x * s, this->y * s);}
        float2 operator/(float s) const {return float2(this->x / s, this->y / s);}
        void operator+=(const float2& o) {this->x += o.x; this->y += o.y;}
        void operator-=(const float2& o) {this->x -= o.x; this->y -= o.y;}
        void operator*=(float s) {this->x *= s; this->y *= s;}
        void operator/=(float s) {this->x /= s; this->y /= s;}
        bool operator==(const float2& o) {return this->x == o.x && this->y == o.y;}

        /* STATIC METHODS */

        // returns the distance between two points
        static float distance(const float2& a, const float2& b) {return (a - b).length();}
        // returns the squared distance between two points
        static float squared_distance(const float2& a, const float2& b) {return (a - b).squared_length();}

        // equivalent to float2(0,0)
        static float2 zero() {return float2();};
        // equivalent to float2(1,1)
        static float2 one() {return float2(1, 1);};
};