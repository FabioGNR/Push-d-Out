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

    public:
        CharacterBuilder(engine::ecs::World& world, engine::physics::World& physics, engine::input::InputManager& inputManager)
            : m_ecsWorld(world)
            , m_physicsWorld(physics)
            , m_inputManager(inputManager)
        {
        }
        void build() const override;
    };
}
}
