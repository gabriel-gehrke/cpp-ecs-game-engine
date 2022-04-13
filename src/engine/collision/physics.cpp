#include "engine/collision/physics.hpp"
#include "engine/collision/collider.hpp"
#include "engine/engine.hpp"

void Physics::step() const
{
    const auto size = this->colliders.size();
    for (auto i = 0; i < size; i++)
    {
        const auto& col1 = this->colliders[i];

        for (auto j = i + 1; j < size; j++)
        {
            const auto& col2 = this->colliders[j];
            float2 p;
            float2 n;

            if (col1->collides_with(*col2, p, n))
            {
                for (const auto& [_, component] : col1->entity)
                {
                    component->on_collision_enter(*col1, *col2, p, n);
                }

                for (const auto& [_, component] : col2->entity)
                {
                    component->on_collision_enter(*col2, *col1, p, n);
                }
            }

        }
    }
}