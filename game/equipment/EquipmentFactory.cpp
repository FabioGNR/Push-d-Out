#include "EquipmentFactory.h"
#include "game/components/DimensionComponent.h"
#include "game/components/EquipableComponent.h"
#include "game/components/ItemComponent.h"
#include "game/components/PositionComponent.h"
#include "game/components/SpriteComponent.h"
#include "game/components/WeaponComponent.h"
#include <engine/common/RNG.h>

namespace game {
namespace equipment {
    using namespace components;

    void buildReverseGravity(engine::ecs::Entity& entity,
        engine::ecs::World& ecsWorld)
    {
        ItemComponent itemComponent{ definitions::ItemType::ReverseGravity };
        ecsWorld.addComponent<ItemComponent>(entity, itemComponent);
        SpriteComponent spriteComponent{ "assets/items.png", "reverse-gravity" };
        ecsWorld.addComponent<SpriteComponent>(entity, spriteComponent);
    }

    void buildForceGun(engine::ecs::Entity& entity,
        engine::ecs::World& ecsWorld)
    {
        WeaponComponent weaponComponent{ 1, definitions::WeaponType::ForceGun };
        ecsWorld.addComponent<WeaponComponent>(entity, weaponComponent);
        SpriteComponent spriteComponent{ "assets/weapons.png", "force-gun" };
        ecsWorld.addComponent<SpriteComponent>(entity, spriteComponent);
    }

    engine::ecs::Entity& EquipmentFactory::createRandomEquipment(common::Vector2D<double> position) const
    {
        const auto totalTypes = static_cast<int>(m_factories.size());
        const int chosenType = common::RNG::generate(std::min(0, totalTypes - 1), totalTypes - 1);

        engine::ecs::Entity& entity
            = m_world.createEntity();
        // add equipment specific components
        m_factories[chosenType](entity, m_world);
        // add common components
        PositionComponent positionComponent{ position };
        m_world.addComponent<PositionComponent>(entity, positionComponent);
        DimensionComponent dimensionComponent{ common::Vector2D<double>(0.5, 0.5) };
        m_world.addComponent<DimensionComponent>(entity, dimensionComponent);
        return entity;
    }

    EquipmentFactory::EquipmentFactory(engine::ecs::World& world)
        : m_world{ world }
    {
        // initialize the factory types
        // items
        m_itemFactoryMap[definitions::ItemType::ReverseGravity] = buildReverseGravity;
        // weapons
        //m_weaponFactoryMap[definitions::WeaponType::ForceGun] = buildForceGun;
        // build vector of factories using the maps
        for (const auto& factoryPair : m_itemFactoryMap) {
            m_factories.push_back(factoryPair.second);
        }
        for (const auto& factoryPair : m_weaponFactoryMap) {
            m_factories.push_back(factoryPair.second);
        }
    }
}
}
