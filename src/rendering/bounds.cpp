#include "rendering/bounds.hpp"

Bounds::Bounds() : Bounds(float2(), float2()) {}
Bounds::Bounds(float2 min, float2 max)
{
    this->min = min;
    this->max = max;
}

float Bounds::width() const
{
    return this->max.x - this->min.x;
}

float Bounds::height() const
{
    return this->max.y - this->min.y;
}

bool Bounds::intersects(const Bounds& o) const
{
    // intersection occurs if difference of max and min coords is smaller than the sum of widths (in both directions)

    const float min_x = std::min(this->min.x, o.min.x);
    const float max_x = std::max(this->max.x, o.max.x);
    if (this->width() + o.width() < max_x - min_x)
    {
        return false;
    }

    const float min_y = std::min(this->min.y, o.min.y);
    const float max_y = std::max(this->max.y, o.max.y);
    if (this->height() + o.height() < max_y - min_y)
    {
        return false;
    }

    return true;
}

Bounds Bounds::from_pos_and_size(const float2& pos, const float2& size)
{
    const float2 hsize = size * 0.5f;
    return Bounds(pos - hsize, pos + hsize);
}