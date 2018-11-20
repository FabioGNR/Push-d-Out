#pragma once

#include "IBuilder.h"
#include <engine/input/InputManager.h>
#include <engine/physics/World.h>

namespace game {
namespace builders {
    class CharacterBuilder : public IBuilder {
    protected:
        engine::ecs::World& m_ecsWorld;
        engine::physics::World& m_physicsWorld;
        engine::input::InputManager& m_inputManager;
        std::string assetsFolder = "assets/sprites/players/";
        size_t m_playerCount;

    public:
        CharacterBuilder(engine::ecs::World& world, engine::physics::World& physics, engine::input::InputManager& inputManager, size_t playerCount = 1)
            : m_ecsWorld(world)
            , m_physicsWorld(physics)
            , m_inputManager(inputManager)
            , m_playerCount(playerCount)
        {
        }
        void build() const override;
    };
}
}
