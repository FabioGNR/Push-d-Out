#pragma once

#include <engine/ecs/World.h>
#include <engine/physics/ContactListener.h>
#include <engine/physics/World.h>
#include <game/components/PortalComponent.h>

namespace game {
namespace listeners {
    class PortalContactListener : public engine::physics::ContactListener {
    private:
        engine::ecs::World* m_ecsWorld;

        void teleport(engine::ecs::Entity& portal, engine::ecs::Entity& player);
        void reset(engine::ecs::Entity& player);
        engine::ecs::Entity* findOtherPortal(engine::ecs::EntityId);

    public:
        explicit PortalContactListener(engine::ecs::World& world)
            : m_ecsWorld{ &world } {};

        void beginContact(engine::physics::Contact contact) override;
        void endContact(engine::physics::Contact contact) override;
    };
}
}
