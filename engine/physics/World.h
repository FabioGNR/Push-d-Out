#pragma once

#include <common/Vector2D.h>
#include <vector>
#include <memory>

class b2World;

namespace engine {
namespace physics {
    class Body;
    class World {
    private:
        friend class DynamicBody;
        friend class StaticBody;

        constexpr static double m_timeStep = 1.0 / 60.0;
        constexpr static int m_velocityIterations = 6;
        constexpr static int m_positionIterations = 2;

        std::unique_ptr<common::Vector2D> m_gravity;
        std::unique_ptr<common::Vector2D> m_friction;
        std::vector<Body*> m_bodies;

        common::Vector2D m_size;
        int m_unitSize;

    public:
        explicit World(common::Vector2D size, double gravity, double friction, int unitSize);
        ~World();

        void update();
        const common::Vector2D getGravity() const;
        const common::Vector2D getFriction() const;
        const common::Vector2D getSize() const;
        void createStaticBody(int x, int y, int width, int height);
        void createDynamicBody(int x, int y, int width, int height);
        const std::vector<Body*> getBodies() const;

        b2World* m_b2World;
    };
}
}
