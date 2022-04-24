#include "engine/rendering/bounds.hpp"

static bool between(float lb, float val, float ub)
{
    return lb <= val && val <= ub;
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

bool Bounds::contains(const float2& p) const
{
    const auto& min = this->min;
    const auto& max = this->max;
    return between(min.x, p.x, max.x) & between(min.y, p.y, max.y);
}

bool Bounds::contains(const Bounds& bounds) const
{
    return this->contains(bounds.min) & this->contains(bounds.max);
}