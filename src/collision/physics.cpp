#include "collision/physics.hpp"
#include "collision/collider.hpp"
#include "engine.hpp"

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

            if (col1->collides_with(*col2, p))
            {
                for (const auto& c : col1->entity.components)
                {
                    c->on_collision_enter(*col1, *col2, p);
                }

                for (const auto& c : col2->entity.components)
                {
                    c->on_collision_enter(*col2, *col1, p);
                }
            }

        }
    }
}