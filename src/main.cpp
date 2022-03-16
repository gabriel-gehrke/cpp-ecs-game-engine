#include "simd.hpp"
#include "entity.hpp"
#include <iostream>

int main()
{
    float4 a = {1, 2, 3, 0};
    float4 b = {2, 1, 0, 69};
    auto c = a + b;
    for (auto i = 0; i < 4; i++)
    {
        std::cout << c[i] << "\n";
    }
    std::cout << "\n";
    auto d = c * 3.0f;
    for (auto i = 0; i < 4; i++)
    {
        std::cout << d[i] << "\n";
    }
    std::cout << "\n";

    Entity player = Entity();
    std::cout << player.id << "\n";

    return 0;
}