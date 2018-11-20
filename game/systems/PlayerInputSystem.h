#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <engine/input/KeyMap.h>
#include <engine/sound/ISoundManager.h>
#include <engine/sound/SDL/SDLSoundManager.h>

namespace game {
namespace systems {
    class PlayerInputSystem : public engine::ecs::BaseSystem<PlayerInputSystem> {
    private:
        engine::ecs::World& m_world;
        const engine::input::KeyMap& m_keyMap;
        std::unique_ptr<engine::sound::ISoundManager> m_soundManager;

    public:
        PlayerInputSystem(engine::ecs::World& world, engine::input::InputManager& inputManager)
            : m_world{ world }
            , m_keyMap{ inputManager.getKeyMap() }
        {
            m_soundManager = std::make_unique<engine::sound::SDLSoundManager>();
        };

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
