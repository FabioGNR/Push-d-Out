#pragma once
#include <random>

namespace common {
class RNG {

    // Disable instantiation of RNG object
    RNG() = default;
    RNG(const RNG&) = default; // Copy constructor
    RNG(RNG&&) = default; // Move constructor
    RNG& operator=(const RNG&) = default; // Copy assignment operator
    RNG& operator=(RNG&&) = default; // Move assignment operator
    virtual ~RNG() = default;

public:
    static int generate(int min, int max);
};
}
