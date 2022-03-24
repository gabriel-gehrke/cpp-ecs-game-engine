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

        // returns a vector, which is orthogonal to this vector (rotated by 90 degrees)
        float2 orthogonal() const {return float2(-this->y, this->x);}

        // returns a reflected copy of this vector, reflected using the given normal
        float2 reflect(const float2& n) const {return *this - n*(2*n.dot(*this));}

        // rotates the point described by this vector around a specified point with the specified angle
        float2 rotate_around(const float2& p, float degrees) const
        {
            // translate to origin
            float2 v = *this - p;
            const float x = v.x;
            const float y = v.y;

            // rotate around origin
            const float radians = degrees * (M_PI / 180.0);
            const float cosr = std::cos(radians);
            const float sinr = std::sin(radians);
            v.x = (x * cosr) - (y * sinr);
            v.y = (y * cosr) + (x * sinr);

            // translate back
            return v + p;
        }

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