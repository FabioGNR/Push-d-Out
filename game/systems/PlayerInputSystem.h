#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <engine/input/KeyMap.h>

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
