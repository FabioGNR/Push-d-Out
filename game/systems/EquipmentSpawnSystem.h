#pragma once

#include <engine/ecs/System.h>
#include <engine/graphics/IRenderer.h>

#include "game/equipment/EquipmentFactory.h"
#include <chrono>
#include <engine/ecs/World.h>

namespace game {
namespace systems {
    class EquipmentSpawnSystem : public engine::ecs::BaseSystem<EquipmentSpawnSystem> {
    public:
        explicit EquipmentSpawnSystem(engine::ecs::World& world)
            : m_world{ world }
            , m_equipmentFactory{ m_world }
        {
        }

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;

    private:
        const common::Vector2D<double> m_spawnOffset{ 0.2, 0.5 };
        engine::ecs::World& m_world;
        equipment::EquipmentFactory m_equipmentFactory;
    };
}
}