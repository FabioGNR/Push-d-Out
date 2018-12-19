#pragma once

#include "PortalContactListener.h"
#include <engine/ecs/World.h>
#include <engine/physics/ContactListener.h>
#include <engine/physics/World.h>
#include <game/components/PortalComponent.h>
#include <game/definitions/ProjectileType.h>

namespace game {
namespace listeners {
    class ProjectileContactListener : public engine::physics::ContactListener {

        struct ProjectileContactData{
            common::Vector2D<double> position;
            common::Vector2D<double> dimension;
            common::Vector2D<double> contactNormal;
            common::Vector2D<double> direction;
            game::definitions::ProjectileType type;
        };

    private:
        constexpr static double GRENADE_RADIUS = 9;

        struct PortalBlueprint {
            ProjectileContactData container;
            bool isAlternative;
        };

        engine::ecs::World* m_ecsWorld;
        engine::physics::World* m_physicsWorld;
        std::vector<PortalBlueprint> m_portalsToBuild;

        void act(ProjectileContactData projectile, engine::ecs::Entity& body);
        void createPortal(ProjectileContactData projectile, bool alternative);
        void createPortalNextUpdate(ProjectileContactData projectile, bool alternative);
        void applyForce(engine::ecs::Entity& body, ProjectileContactData projectile);
        void explode(ProjectileContactData projectile, double radius);
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
