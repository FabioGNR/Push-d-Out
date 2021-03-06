#pragma once

#include "Body.h"

#include <engine/common/Vector2D.h>

#include <chrono>
#include <memory>
#include <vector>

class b2World;
class b2Body;
struct b2BodyDef;

namespace engine {
namespace physics {
    class World {
    private:
        constexpr static int m_velocityIterations = 6;
        constexpr static int m_positionIterations = 2;

        // Use PIMPL-idiom to hide implementation details
        // this is needed because unique_ptr needs to know the full implementation of b2World
        // and forward declaration is not good enough
        class WorldImpl;
        std::unique_ptr<WorldImpl> m_impl;

    public:
        World(common::Vector2D<int> size, double gravity, double friction);

        World(const World& other) = delete;
        World& operator=(const World& other) = delete;

        World(World&& other) = default;
        World& operator=(World&& other) = default;

        virtual ~World();

        void update(std::chrono::nanoseconds deltaTime);
        const common::Vector2D<double>& getGravity() const;
        const common::Vector2D<double>& getFriction() const;
        const common::Vector2D<int>& getSize() const;

        b2Body* createBody(const b2BodyDef& def) const;
        void destroyBody(b2Body* body);

        const Body* createStaticBody(common::Vector2D<double> position, common::Vector2D<double> dimension);
        const Body* createDynamicBody(common::Vector2D<double> position, common::Vector2D<double> dimension);
        const Body* createKinematicBody(common::Vector2D<double> position, common::Vector2D<double> dimension);
        const std::vector<std::unique_ptr<Body>>& getBodies() const;
    };
}
}
