#include "EquipmentFactory.h"
#include "game/components/DimensionComponent.h"
#include "game/components/EquipableComponent.h"
#include "game/components/ItemComponent.h"
#include "game/components/PositionComponent.h"
#include "game/components/SpriteComponent.h"
#include "game/components/WeaponComponent.h"
#include <engine/common/RNG.h>
#include <game/builders/SpriteBuilder.h>

using factorySignature = std::function<void(engine::ecs::Entity&, engine::ecs::World&, std::map<std::string, game::components::SpriteComponent>)>;

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
        WeaponComponent weaponComponent{ definitions::WeaponType::ForceGun, 1, definitions::ProjectileType::Force };
        ecsWorld.addComponent<WeaponComponent>(entity, weaponComponent);
        auto spriteComponentPair = spriteComponentMap.find("ForceGun");
        if (spriteComponentPair != spriteComponentMap.end()) {
            auto spriteComponent = spriteComponentPair->second;
            ecsWorld.addComponent<components::SpriteComponent>(entity, spriteComponent);
        }
    }

    void buildGrenadeLauncher(engine::ecs::Entity& entity,
                       engine::ecs::World& ecsWorld,
                       std::map<std::string, components::SpriteComponent> spriteComponentMap)
    {
        WeaponComponent weaponComponent{ definitions::WeaponType::GrenadeLauncher, 3, definitions::ProjectileType::Grenade };
        ecsWorld.addComponent<WeaponComponent>(entity, weaponComponent);
        auto spriteComponentPair = spriteComponentMap.find("GrenadeLauncher");
        if (spriteComponentPair != spriteComponentMap.end()) {
            auto spriteComponent = spriteComponentPair->second;
            ecsWorld.addComponent<components::SpriteComponent>(entity, spriteComponent);
        }
    }

    void buildPortalGun(engine::ecs::Entity& entity,
        engine::ecs::World& ecsWorld,
        std::map<std::string, components::SpriteComponent> spriteComponentMap)
    {
        WeaponComponent weaponComponent(definitions::WeaponType::PortalGun, 1,
            definitions::ProjectileType::BluePortal, 1, definitions::ProjectileType::OrangePortal);
        ecsWorld.addComponent<WeaponComponent>(entity, weaponComponent);
        auto spriteComponentPair = spriteComponentMap.find("PortalGun");
        if (spriteComponentPair != spriteComponentMap.end()) {
            auto spriteComponent = spriteComponentPair->second;
            ecsWorld.addComponent<components::SpriteComponent>(entity, spriteComponent);
        }
    }

    engine::ecs::Entity& EquipmentFactory::createRandomEquipment(common::Vector2D<double> position) const
    {
        const auto totalTypes = static_cast<int>(m_factories.size());
        const int chosenType = common::RNG::generate(std::min(0, totalTypes - 1), totalTypes - 1);

        engine::ecs::Entity& entity = m_world.createEntity();
        // add equipment specific components
        auto equipment = m_factories[chosenType];
        equipment.first(entity, m_world, m_spriteComponentMap);
        // add common components
        DimensionComponent dimensionComponent{ equipment.second };
        m_world.addComponent<DimensionComponent>(entity, dimensionComponent);
        PositionComponent positionComponent{ position - (dimensionComponent.dimension / 2) };
        positionComponent.position.y += .5;
        m_world.addComponent<PositionComponent>(entity, positionComponent);

        return entity;
    }

    std::pair<factorySignature, common::Vector2D<double>> pair(factorySignature func, common::Vector2D<double> size)
    {
        return std::pair(func, size);
    }

    EquipmentFactory::EquipmentFactory(engine::ecs::World& world)
        : m_world{ world }
    {
        // initialize the factory types
        // items
        m_itemFactoryMap[definitions::ItemType::ReverseGravity] = pair(buildReverseGravity, common::Vector2D<double>(1, 1));
        // weapons
        m_weaponFactoryMap[definitions::WeaponType::GrenadeLauncher] = pair(buildGrenadeLauncher, common::Vector2D<double>(2,1));
        m_weaponFactoryMap[definitions::WeaponType::PortalGun] = pair(buildPortalGun, common::Vector2D<double>(2, 1));
        m_weaponFactoryMap[definitions::WeaponType::ForceGun] = pair(buildForceGun, common::Vector2D<double>(2, 1));

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

    engine::ecs::Entity& EquipmentFactory::get(definitions::WeaponType weaponType)
    {
        engine::ecs::Entity& entity = m_world.createEntity();
        m_weaponFactoryMap[weaponType].first(entity, m_world, m_spriteComponentMap);
        return entity;
    }

    engine::ecs::Entity& EquipmentFactory::get(definitions::ItemType itemType)
    {
        engine::ecs::Entity& entity = m_world.createEntity();
        m_itemFactoryMap[itemType].first(entity, m_world, m_spriteComponentMap);
        return entity;
    }
}
}
