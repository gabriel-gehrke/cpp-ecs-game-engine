#pragma once

#include <string>

struct Resource
{
    const std::string path;
    const void* data;
    const size_t size;

    public:
        static const Resource& load(const std::string path);
};