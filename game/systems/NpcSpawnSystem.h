#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/physics/World.h>
#include <game/builders/CharacterSpawnGenerator.h>
#include <utility>

namespace game::systems {
class NpcSpawnSystem : public engine::ecs::BaseSystem<NpcSpawnSystem> {
private:
    static constexpr std::chrono::nanoseconds COOLDOWN = std::chrono::milliseconds(10000);
    static const int MAX_BUNNIES = 5;

    engine::ecs::World* m_world;
    engine::physics::World* m_physics;

    std::vector<common::Vector2D<double>> m_spawnPositions = builders::CharacterSpawnGenerator::collect(*m_world);
    std::chrono::nanoseconds m_cooldown = COOLDOWN;

public:
    NpcSpawnSystem(engine::ecs::World* world, engine::physics::World* physics)
        : m_world(world)
        , m_physics(physics)
    {
    }

    void render(engine::IRenderer& renderer) override;
    void update(std::chrono::nanoseconds timeStep) override;
};
}
