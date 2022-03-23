#pragma once

#include <cstdint>
#include <array>

uint64_t rand64();

struct uuid
{
    public:
        // 256 bits of random numbers 
        std::array<uint64_t, 4> ints = {rand64(), rand64(), rand64(), rand64()};

        bool operator==(const uuid& o) const {return this->ints == o.ints;}
};

uuid randid();
