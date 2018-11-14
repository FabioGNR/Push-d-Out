#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <engine/input/maps/KeyMap.h>
#include <engine/sound/ISoundManager.h>
#include <engine/sound/SDL/SDLSoundManager.h>

namespace game {
namespace systems {
    class PlayerInputSystem : public engine::ecs::BaseSystem<PlayerInputSystem> {
    private:
        engine::ecs::World& m_world;
/*
        engine::input::maps::InputMap& m_keyMap;

    public:
        PlayerInputSystem(engine::ecs::World& world, engine::input::InputManager& inputManager)
            : m_world { world }
            , m_keyMap { inputManager.getMap() } {};*/
        engine::input::maps::InputMap& m_keyMap;
        std::unique_ptr<engine::sound::ISoundManager> m_soundManager;

    public:
        PlayerInputSystem(engine::ecs::World& world, engine::input::InputManager& inputManager)
            : m_world{ world }
                , m_keyMap { inputManager.getMap() }
        {
            m_soundManager = std::make_unique<engine::sound::SDLSoundManager>();
        };

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
        void move(common::Vector2D<double>& delta, bool invert);
        void jump(common::Vector2D<double>& delta);
    };
}
}
