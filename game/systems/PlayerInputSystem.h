#pragma once

#include "engine/ecs/System.h"
#include <ecs/World.h>
#include <input/InputManager.h>
#include <input/KeyMap.h>

namespace game {
namespace systems {
    class PlayerInputSystem : public engine::ecs::BaseSystem<PlayerInputSystem> {
    private:
        engine::ecs::World& m_world;
        const engine::input::KeyMap& m_keyMap;

    public:
        PlayerInputSystem(engine::ecs::World& world, engine::input::InputManager& inputManager)
            : m_world{ world }
            , m_keyMap{ inputManager.getKeyMap() } {};

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
