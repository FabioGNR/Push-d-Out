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
        constexpr static double FORCE_GUN_RADIUS = 6;

        struct PortalBlueprint {
            engine::ecs::Entity* entity;
            bool isAlternative;
            engine::physics::Contact* contact;
        };

        engine::ecs::World* m_ecsWorld;
        engine::physics::World* m_physicsWorld;
        std::vector<PortalBlueprint> m_portalsToBuild;

        void act(engine::ecs::Entity& projectile, engine::ecs::Entity& body, engine::physics::Contact& contact);
        void createPortal(engine::ecs::Entity& projectile, engine::physics::Contact& contact, bool alternative);
        void createPortalNextUpdate(engine::ecs::Entity& projectile, engine::physics::Contact& contact, bool alternative);
        void applyForce(engine::ecs::Entity& body, engine::physics::Contact& contact);
        void explode(engine::ecs::Entity& projectile, double radius);
        engine::ecs::Entity* findPortal(bool alternative);

    public:
        explicit ProjectileContactListener(engine::ecs::World* world, engine::physics::World* physics)
            : m_ecsWorld{ world }
            , m_physicsWorld{ physics } {};

        void beginContact(engine::physics::Contact& contact) override;
        void endContact(engine::physics::Contact& contact) override;
        void preSolve(engine::physics::Contact& contact) override;
        void postSolve(engine::physics::Contact& contact) override;
        void update(std::chrono::nanoseconds nanoseconds) override;
    };
}
}
