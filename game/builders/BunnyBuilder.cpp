#include "BunnyBuilder.h"
#include "SpriteBuilder.h"
#include <game/components/AIComponent.h>
#include <game/components/AnimationsComponent.h>
#include <game/components/BodyComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/OnOutOfBoundsDeleteComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/config/ConfigurationRepository.h>
#include <game/definitions/BodyGroupIndex.h>

namespace game::builders {
BunnyBuilder::BunnyBuilder(engine::ecs::World* w, engine::physics::World* p)
    : m_world{ w }
    , m_physics{ p }
{
    m_entity = &w->createEntity();
}

engine::ecs::Entity* BunnyBuilder::build()
{
    m_world->addComponent<components::BodyComponent>(*m_entity, m_physics->createDynamicBody(m_position, m_dimensions, m_entity->id(), static_cast<int>(definitions::BodyGroupIndex::NPC)));
    m_world->addComponent<components::AIComponent>(*m_entity);
    m_world->addComponent<components::MoveComponent>(*m_entity, common::Vector2D<double>(0, 0), true);
    m_world->addComponent<components::OnOutOfBoundsDeleteComponent>(*m_entity);
    addSprites();
    return m_entity;
}

BunnyBuilder& BunnyBuilder::setPosition(common::Vector2D<double> pos)
{
    m_position = pos;
    m_world->addComponent<components::PositionComponent>(*m_entity, pos);
    return *this;
}

BunnyBuilder& BunnyBuilder::setDimensions(common::Vector2D<double> dimensions)
{
    m_dimensions = dimensions;
    m_world->addComponent<components::DimensionComponent>(*m_entity, dimensions);
    return *this;
}

void BunnyBuilder::addSprites()
{
    auto levelMetaComponent = m_world->begin<components::LevelMetaComponent>();
    if (levelMetaComponent != m_world->end<components::LevelMetaComponent>()) {
        auto config = config::ConfigurationRepository::get();
        const auto& themeName = static_cast<components::LevelMetaComponent*>(levelMetaComponent->second.get())->theme;
        const auto& imagePath = config.assets + "sprites/themes/" + themeName.sprites + "/npc.png";
        const auto& datafilePath = config.assets + "sprites/themes/npc.json";
        auto sheet = builders::SpriteBuilder{ imagePath, datafilePath }.build();
        auto sprite = sheet.at("BunnyIdle");

        m_world->addComponent<components::SpriteComponent>(*m_entity, sprite.sprites, sprite.frameCount, sprite.frameTime);
        m_world->addComponent<components::AnimationsComponent>(*m_entity, sheet);
    }
}
}
