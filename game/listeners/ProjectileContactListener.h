#pragma once

#include "PortalContactListener.h"
#include <engine/ecs/World.h>
#include <engine/physics/ContactListener.h>
#include <engine/physics/World.h>
#include <game/components/PortalComponent.h>

namespace game {
namespace listeners {
    class ProjectileContactListener : public engine::physics::ContactListener {
    private:
        engine::ecs::World* m_ecsWorld;
        engine::physics::World* m_physicsWorld;
        constexpr static double FORCE_GUN_RADIUS = 6;

        void act(engine::ecs::Entity& projectile, engine::ecs::Entity& body, common::Vector2D<double> position);
        void createPortal(common::Vector2D<double> position, bool alternative);
        void applyForce(engine::ecs::Entity& body, engine::ecs::Entity& projectile);
        void explode(engine::ecs::Entity& projectile, double radius);
        engine::ecs::Entity* findPortal(bool alternative);

    public:
        explicit ProjectileContactListener(engine::ecs::World* world, engine::physics::World* physics)
            : m_ecsWorld{ world }
            , m_physicsWorld{ physics } {};

        void beginContact(engine::physics::Contact contact) override;
        void endContact(engine::physics::Contact contact) override;
    };
}
}
