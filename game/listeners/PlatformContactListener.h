#pragma once

#include <engine/ecs/World.h>
#include <engine/input/maps/InputMaps.h>
#include <engine/physics/ContactListener.h>

namespace game {
namespace listeners {
    class PlatformContactListener : public engine::physics::ContactListener {
    private:
        engine::ecs::World* m_world;
        engine::input::maps::InputMaps* m_inputMaps;

        void disableContact(engine::physics::Contact& contact,
            engine::ecs::Entity& player,
            engine::ecs::Entity& tile);

    public:
        explicit PlatformContactListener(engine::ecs::World& world, engine::input::maps::InputMaps* inputMaps)
            : m_world{ &world }
            , m_inputMaps{ inputMaps } {};

        void beginContact(engine::physics::Contact& contact) override;
        void endContact(engine::physics::Contact&) override;
        void preSolve(engine::physics::Contact&) override;
        void postSolve(engine::physics::Contact&) override;
    };
}
}
