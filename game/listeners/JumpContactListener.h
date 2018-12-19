#pragma once

#include <engine/ecs/World.h>
#include <engine/physics/ContactListener.h>
namespace game {
namespace listeners {
    class JumpContactListener : public engine::physics::ContactListener {
    private:
        engine::ecs::World* m_world;

        void resetJump(engine::ecs::Entity&);

    public:
        explicit JumpContactListener(engine::ecs::World& world)
            : m_world{ &world } {};

        void beginContact(engine::physics::Contact contact) override;
        void endContact(engine::physics::Contact contact) override;
    };
}
}
