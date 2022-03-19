#include "random.hpp"
#include <cstdlib>
#include <sys/time.h>
#include <iostream>

static bool was_seeded = false;

static void seed()
{
    if (was_seeded) return;

    // get time
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // generate time from xoring time bytes
    uint* ptr = (uint*) &tv;
    uint seed = 0;
    for (auto i = 0; i < sizeof(timeval) / sizeof(uint); i++)
    {
        seed ^= *ptr++;
    }

    // seed the rng from cstdlib
    srand(seed);
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