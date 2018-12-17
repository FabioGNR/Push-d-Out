#include "NpcSpawnSystem.h"
#include "PlayerInputSystem.h"
#include "game/components/DimensionComponent.h"
#include "game/components/PositionComponent.h"
#include "game/components/SpriteComponent.h"
#include <engine/common/RNG.h>
#include <engine/common/Vector2D.h>
#include <engine/exceptions/EntityNotFoundException.h>
#include <game/ai/IdleBehaviour.h>
#include <game/ai/WanderingBehaviour.h>
#include <game/builders/BunnyBuilder.h>
#include <game/components/AIComponent.h>
#include <game/components/TileComponent.h>
#include <random>

namespace game {
namespace systems {
    void NpcSpawnSystem::update(std::chrono::nanoseconds timeStep)
    {
        int count = 0;
        for (auto it = m_world->begin<components::AIComponent>(); it != m_world->end<components::AIComponent>(); ++it) {
            ++count;
        }

        // update cooldown and check if it has passed
        if ((m_cooldown -= timeStep).count() <= 0 && count < MAX_BUNNIES) {
            auto size = m_world->size<components::TileComponent>();
            int index = common::RNG::generate(0, static_cast<int>(size - 1));

            auto it = m_world->begin<components::TileComponent>();
            while (index > 0 && it != m_world->end<components::TileComponent>()) {
                ++it, --index; // search random tile
            }

            try {
                auto& entity = m_world->getEntity(it->first);
                auto position = m_world->getComponent<components::PositionComponent>(entity).position;
                auto dimensions = m_world->getComponent<components::DimensionComponent>(entity).dimension;
                position.y += dimensions.y; // spawn bunny on top of the tile

                game::builders::BunnyBuilder bunnyBuilder{ m_world, m_physics };
                auto bunnyEntity = bunnyBuilder.setPosition(position)
                                       .setDimensions(common::Vector2D<double>(1, 1))
                                       .build();

                auto& bunny = m_world->getComponent<components::AIComponent>(*bunnyEntity);
                bunny.behaviours[definitions::AIState::WANDERING] = std::make_unique<ai::WanderingBehaviour>(m_world, m_physics, bunnyEntity);
                bunny.behaviours[definitions::AIState::IDLE] = std::make_unique<ai::IdleBehaviour>(m_world, m_physics, bunnyEntity);

                bunny.state(definitions::AIState::IDLE);
            } catch (engine::exceptions::EntityNotFoundException& e) {
                return; // try again next update
            }

            m_cooldown = COOLDOWN;
        }
    }

    void NpcSpawnSystem::render(engine::IRenderer& /* renderer */)
    {
    }
}
}
