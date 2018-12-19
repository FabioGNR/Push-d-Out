#include "WanderingBehaviour.h"
#include <engine/common/RNG.h>
#include <game/builders/SpriteBuilder.h>
#include <game/components/AIComponent.h>
#include <game/components/AnimationsComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/config/ConfigurationRepository.h>
#include <game/level/Tiles.h>

namespace game::ai {
void WanderingBehaviour::act(std::chrono::nanoseconds /* delta */)
{
    auto& ai = m_world->getComponent<components::AIComponent>(*m_entity);

    if (ai.target == nullptr) {
        setTarget();
    }

    if (ai.target != nullptr) {
        auto targetPosition = m_world->getComponent<components::PositionComponent>(*ai.target).position;
        targetPosition.y += 1; // we don't want to target the tile but space above the tile
        auto entityPosition = m_world->getComponent<components::PositionComponent>(*m_entity).position;

        if (targetPosition.approximatelyEquals(entityPosition, 0.05)) {
            return ai.state(definitions::AIState::IDLE);
        }

        auto distance = targetPosition - entityPosition;
        distance.y = 0;

        auto& sprite = m_world->getComponent<components::SpriteComponent>(*m_entity);
        for (auto& s : sprite.sprites) {
            s.flippedHorizontal = distance.x > 0;
        }

        auto& move = m_world->getComponent<components::MoveComponent>(*m_entity);
        move.delta = distance.normalize() * 2;
    }
}

void WanderingBehaviour::setTarget()
{
    auto& ai = m_world->getComponent<components::AIComponent>(*m_entity);
    auto position = m_world->getComponent<components::PositionComponent>(*m_entity).position;
    position.y -= 1;

    auto* groundEntity = level::Tiles::get(*m_world, position.castTo<int>());
    if (groundEntity != nullptr) {
        ai.target = findEdge(groundEntity, static_cast<bool>(common::RNG::generate(0, 1)));
    }
}

engine::ecs::Entity* WanderingBehaviour::findEdge(engine::ecs::Entity* entity, bool left)
{
    auto position = m_world->getComponent<components::PositionComponent>(*entity).position.castTo<int>();
    left ? position.x -= 1 : position.x += 1;
    auto* next = level::Tiles::get(*m_world, position);

    if (next == nullptr) {
        return entity;
    } else {
        return findEdge(next, left);
    }
}

void WanderingBehaviour::init()
{
    auto& ai = m_world->getComponent<components::AIComponent>(*m_entity);
    ai.target = nullptr;
    if (m_entity->hasComponent<components::AnimationsComponent>()) {
        auto animations = m_world->getComponent<components::AnimationsComponent>(*m_entity).animations;
        auto sprite = animations.at("BunnyWalking");
        m_world->removeComponent<components::SpriteComponent>(*m_entity);
        m_world->addComponent<components::SpriteComponent>(*m_entity, sprite.sprites, sprite.frameCount,
            sprite.frameTime);
    }
}

void WanderingBehaviour::exit()
{
    auto& ai = m_world->getComponent<components::AIComponent>(*m_entity);
    ai.target = nullptr;
}
}
