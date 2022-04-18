#include "engine/random.hpp"
#include <cstdlib>
#include <sys/time.h>

static bool was_seeded = false;

static void seed()
{
    if (was_seeded) return;

    // get time
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // generate seed from processing time bytes
    uint* ptr = (uint*) &tv;
    uint seed = 0xabcdef5;

    for (uint i = 0; i < sizeof(timeval) / sizeof(uint); i++)
    {
        uint v = ptr[i];
        v += seed * (v % 2);

        seed ^= v;
    }

    // seed the rng from cstdlib
    srand(seed);
    was_seeded = true;
}

uint32_t rand32()
{
    seed();
    return (rand() << 16) | (rand() & 0xFFFF);
}

uint64_t rand64()
{
    seed();

    uint64_t r = 0;
    auto ptr = (uint16_t*) &r;
    for (auto i = 0; i < 4; i++)
    {
        *ptr++ = (uint16_t)(rand() & 0xFFFF);
    }
    return r;
}

uint32_t randrange(const uint32_t lb, const uint32_t ub)
{
    return lb + (rand32() % (ub - lb));
}

uuid randid()
{
    return uuid();
}