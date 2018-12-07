#pragma once

#include "PortalContactListener.h"
#include <engine/ecs/World.h>
#include <engine/physics/ContactListener.h>
#include <engine/physics/World.h>
#include <game/components/PortalComponent.h>

namespace game {
namespace listeners {
    class ProjectilePortalContactListener : public engine::physics::ContactListener {
    private:
        engine::ecs::World* m_ecsWorld;

        void teleportProjectile(engine::ecs::Entity& projectile, engine::ecs::Entity& portal);
        engine::ecs::Entity* findOtherPortal(engine::ecs::EntityId id);

    public:
        explicit ProjectilePortalContactListener(engine::ecs::World* world)
            : m_ecsWorld{ world } {};

        void beginContact(engine::physics::Contact contact) override;
        void endContact(engine::physics::Contact contact) override;
    };
}
}
