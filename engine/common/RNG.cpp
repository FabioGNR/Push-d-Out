#include "RNG.h"

struct Impl {
    std::mt19937 rng;
    Impl()
        : rng(std::random_device{}())
    {
    }
};

namespace common {
int RNG::generate(const int min, const int max)
{
    static Impl impl;

    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(impl.rng);
}
}
