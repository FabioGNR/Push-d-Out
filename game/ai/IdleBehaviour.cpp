#include "IdleBehaviour.h"
#include <game/builders/SpriteBuilder.h>
#include <game/components/AIComponent.h>
#include <game/components/AnimationsComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/config/ConfigurationRepository.h>

namespace game::ai {
void IdleBehaviour::act(std::chrono::nanoseconds deltaTime)
{
    m_timeout -= deltaTime;
    if (m_timeout.count() <= 0) {
        auto& ai = m_world->getComponent<components::AIComponent>(*m_entity);
        m_timeout = COOLDOWN;

        ai.state(definitions::AIState::WANDERING);
    }
}

void IdleBehaviour::init()
{
    m_timeout = COOLDOWN;
    if (m_entity->hasComponent<components::AnimationsComponent>()) {
        auto animations = m_world->getComponent<components::AnimationsComponent>(*m_entity).animations;
        auto sprite = animations.at("BunnyIdle");
        m_world->removeComponent<components::SpriteComponent>(*m_entity);
        m_world->addComponent<components::SpriteComponent>(*m_entity, sprite.sprites, sprite.frameCount,
            sprite.frameTime);
    }
}

void IdleBehaviour::exit()
{
}
}
