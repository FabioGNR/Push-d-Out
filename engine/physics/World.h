#pragma once

#include "Body.h"
#include "ContactListener.h"
#include "RaycastHit.h"
#include <engine/common/Vector2D.h>
#include <engine/ecs/Entity.h>

#include <chrono>
#include <functional>
#include <memory>
#include <vector>

class b2World;
class b2Body;
struct b2BodyDef;

namespace engine {
namespace physics {
    // body = body that was hit
    // point = where the body was hit
    // normal = angle of hit
    // fraction = where on the line was the hit (0-1)
    // returns new maximum fraction (-1 to leave unchanged)
    using RaycastCallback = std::function<double(const RaycastHit& hit)>;

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

        void update(std::chrono::nanoseconds);

        common::Vector2D<double> getGravity() const;
        const common::Vector2D<double>& getFriction() const;
        const common::Vector2D<int>& getSize() const;
        void setGravity(common::Vector2D<double> gravity);

        void raycast(const common::Vector2D<double>& start, const common::Vector2D<double>& end, const RaycastCallback& callback);

        b2Body* createBody(const b2BodyDef& def) const;
        void destroyBody(Body* body, b2Body* b2Body);

        void addContactListener(std::unique_ptr<ContactListener> contactListener);

        std::unique_ptr<Body> createStaticBody(common::Vector2D<double> position, common::Vector2D<double> dimension, ecs::EntityId);
        std::unique_ptr<Body> createDynamicBody(common::Vector2D<double> position, common::Vector2D<double> dimension, ecs::EntityId);
        std::unique_ptr<Body> createKinematicBody(common::Vector2D<double> position, common::Vector2D<double> dimension, ecs::EntityId);
    };
}
}
