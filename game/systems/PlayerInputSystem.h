#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <engine/sound/ISoundManager.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <game/components/DirectionComponent.h>

namespace game {
namespace systems {
    class PlayerInputSystem : public engine::ecs::BaseSystem<PlayerInputSystem> {
    private:
        const double moveDeadZone = 0.5;
        engine::ecs::World& m_world;
        engine::sound::ISoundManager* m_soundManager;
        engine::input::maps::InputMaps* m_inputMaps;

    public:
        PlayerInputSystem(engine::ecs::World& world, engine::input::InputManager* inputManager,
            engine::sound::ISoundManager* soundManager)
            : m_world{ world }
            , m_soundManager{ soundManager }
            , m_inputMaps{ inputManager->getMap() } {};

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
        void move(common::Vector2D<double>& delta, bool invert, components::DirectionComponent& directionComponent);
        void jump(common::Vector2D<double>& delta);
    };
}
}
