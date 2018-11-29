#include "EquipmentFactory.h"
#include "game/components/DimensionComponent.h"
#include "game/components/EquipableComponent.h"
#include "game/components/ItemComponent.h"
#include "game/components/PositionComponent.h"
#include "game/components/SpriteComponent.h"
#include "game/components/WeaponComponent.h"
#include <engine/common/RNG.h>
#include <game/builders/SpriteBuilder.h>

namespace game {
namespace equipment {
    using namespace components;

    void buildReverseGravity(engine::ecs::Entity& entity,
        engine::ecs::World& ecsWorld,
        std::map<std::string, components::SpriteComponent> spriteComponentMap)
    {
        ItemComponent itemComponent{ definitions::ItemType::ReverseGravity };
        ecsWorld.addComponent<ItemComponent>(entity, itemComponent);
        auto spriteComponentPair = spriteComponentMap.find("ReverseGravity");
        if (spriteComponentPair != spriteComponentMap.end()) {
            auto spriteComponent = spriteComponentPair->second;
            ecsWorld.addComponent<components::SpriteComponent>(entity, spriteComponent);
        }
    }

    void buildForceGun(engine::ecs::Entity& entity,
        engine::ecs::World& ecsWorld,
        std::map<std::string, components::SpriteComponent> spriteComponentMap)
    {
        WeaponComponent weaponComponent{ 1, definitions::WeaponType::ForceGun };
        ecsWorld.addComponent<WeaponComponent>(entity, weaponComponent);
        auto spriteComponentPair = spriteComponentMap.find("ReverseGravity");
        if (spriteComponentPair != spriteComponentMap.end()) {
            auto spriteComponent = spriteComponentPair->second;
            ecsWorld.addComponent<components::SpriteComponent>(entity, spriteComponent);
        }
    }

    engine::ecs::Entity& EquipmentFactory::createRandomEquipment(common::Vector2D<double> position) const
    {
        const auto totalTypes = static_cast<int>(m_factories.size());
        const int chosenType = common::RNG::generate(std::min(0, totalTypes - 1), totalTypes - 1);

        engine::ecs::Entity& entity
            = m_world.createEntity();
        // add equipment specific components
        m_factories[chosenType](entity, m_world, m_spriteComponentMap);
        // add common components
        DimensionComponent dimensionComponent{ common::Vector2D<double>(0.5, 0.5) };
        m_world.addComponent<DimensionComponent>(entity, dimensionComponent);
        PositionComponent positionComponent{ position - (dimensionComponent.dimension / 2) };
        m_world.addComponent<PositionComponent>(entity, positionComponent);

        return entity;
    }

    EquipmentFactory::EquipmentFactory(engine::ecs::World& world)
        : m_world{ world }
    {
        // initialize the factory types
        // items
        m_itemFactoryMap[definitions::ItemType::ReverseGravity] = buildReverseGravity;
        // weapons
        m_weaponFactoryMap[definitions::WeaponType::ForceGun] = buildForceGun;
        // build vector of factories using the maps
        for (const auto& factoryPair : m_itemFactoryMap) {
            m_factories.push_back(factoryPair.second);
        }
        for (const auto& factoryPair : m_weaponFactoryMap) {
            m_factories.push_back(factoryPair.second);
        }

        //Build sprite component map
        builders::SpriteBuilder eqSpriteBuilder{ "assets/sprites/equipment/equipment.png",
            "assets/sprites/equipment/equipment.json" };
        m_spriteComponentMap = eqSpriteBuilder.build();
    }
}
}
