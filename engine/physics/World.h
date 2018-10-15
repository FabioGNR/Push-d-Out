#pragma once

#include <chrono>
#include <common/Vector2D.h>
#include <memory>
#include <vector>

class b2World;

namespace engine {
namespace physics {
    class Body;
    class World {
    private:
        friend class DynamicBody;
        friend class StaticBody;

        constexpr static int m_velocityIterations = 6;
        constexpr static int m_positionIterations = 2;

        std::unique_ptr<common::Vector2D<double>> m_gravity;
        std::unique_ptr<common::Vector2D<double>> m_friction;
        std::vector<Body*> m_bodies;

        common::Vector2D<int> m_size;

    public:
        explicit World(common::Vector2D<int> size, double gravity, double friction);
        ~World();

        void update(std::chrono::nanoseconds deltaTime);
        const common::Vector2D<double> getGravity() const;
        const common::Vector2D<double> getFriction() const;
        const common::Vector2D<int> getSize() const;
        const Body* createStaticBody(int x, int y, int width, int height);
        const Body* createDynamicBody(int x, int y, int width, int height);
        const std::vector<Body*> getBodies() const;

        b2World* m_b2World;
    };
}
}
