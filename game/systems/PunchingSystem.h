#pragma once
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <engine/physics/World.h>
#include <engine/sound/ISoundManager.h>
#include <game/components/PunchComponent.h>

namespace game::systems {
class PunchingSystem : public engine::ecs::BaseSystem<PunchingSystem> {
    engine::ecs::World* m_ecsWorld;
    engine::physics::World* m_world;
    engine::input::maps::InputMaps* m_inputMaps;
    engine::sound::ISoundManager* m_soundManager;
    constexpr static double m_punchCooldownSeconds{ 1.5 };
    constexpr static double m_punchRange{ 1 };

    bool attemptHitInDirection(const engine::physics::Body* playerBody, const common::Vector2D<double>& from, const common::Vector2D<double>& to);
    void punch(const engine::ecs::Entity& player, components::PunchComponent& punchComponent);
    void playPunchAnimation(const engine::ecs::Entity& player);
    bool doesPlayerWantToPunch(const engine::ecs::Entity& player) const;

public:
    PunchingSystem(engine::ecs::World* ecsWorld,
        engine::physics::World* world,
        engine::input::InputManager* inputManager,
        engine::sound::ISoundManager* soundManager)
        : m_ecsWorld{ ecsWorld }
        , m_world{ world }
        , m_inputMaps{ inputManager->getMap() }
        , m_soundManager{ soundManager }
    {
    }

    void update(std::chrono::nanoseconds timeStep) override;

    void render(engine::IRenderer& renderer) override;
};
}