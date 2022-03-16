#include "random.hpp"
#include <ctime>

static bool was_seeded = false;

static void seed()
{
    if (was_seeded) return;

    srand(time(NULL));
    was_seeded = true;
}

uint64_t rand64()
{
    seed();

    uint64_t r;
    auto ptr = (uint16_t*) &r;
    for (auto i = 0; i < 4; i++)
    {
        *ptr++ = (uint16_t)(rand() & 0xFFFF);
    }
    return r;
}