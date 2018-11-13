#include "RNG.h"
#include <ctime>

struct Impl {
    std::mt19937 rng;
    Impl()
        : rng(static_cast<unsigned int>(time(nullptr)))
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
} // namespace common
