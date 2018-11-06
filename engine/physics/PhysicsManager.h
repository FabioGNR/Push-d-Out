#pragma once

#include "engine/physics/World.h"

#include <vector>

class b2Body;

namespace engine {
namespace physics {
    class PhysicsManager {
    public:
        PhysicsManager();

        PhysicsManager(const PhysicsManager& other) = default;
        PhysicsManager& operator=(const PhysicsManager& other) = default;

        PhysicsManager(PhysicsManager&& other) = default;
        PhysicsManager& operator=(PhysicsManager&& other) = default;

        virtual ~PhysicsManager();

        std::unique_ptr<World> createWorld(common::Vector2D<int> size, double gravity, double friction);
    };
}
}
