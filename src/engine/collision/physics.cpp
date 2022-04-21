#include "engine/collision/physics.hpp"
#include "engine/collision/collider.hpp"
#include "engine/engine.hpp"
#include "engine/random.hpp"

void Physics::step()
{
    const size_t size = this->colliders.size();

    // basic swapping algorithm
    for (auto i = size; i != 1; i--)
    {
        auto index1 = i - 1;
        auto index2 = rand32() % index1;

        auto temp = this->colliders[index1];
        this->colliders[index1] = this->colliders[index2];
        this->colliders[index2] = temp;
    }

    for (auto i = 0U; i < size; i++)
    {
        const Collider* col1 = this->colliders[i];

        for (auto j = i + 1; j < size; j++)
        {
            const Collider* col2 = this->colliders[j];
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