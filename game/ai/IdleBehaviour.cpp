#include "IdleBehaviour.h"
#include <game/builders/SpriteBuilder.h>
#include <game/components/AIComponent.h>
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
    auto config = config::ConfigurationRepository::get();
    auto sheet = builders::SpriteBuilder{ config.assets + "sprites/npc/bunny.png", config.assets + "sprites/npc/bunny.json" }.build();
    auto sprite = sheet.at("Idle");
    m_world->removeComponent<components::SpriteComponent>(*m_entity);
    m_world->addComponent<components::SpriteComponent>(*m_entity, sprite.sprites, sprite.frameCount, sprite.frameTime);
}

void IdleBehaviour::exit()
{
}
}
