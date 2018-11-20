#pragma once

#include "game/definitions/ItemType.h"
#include "game/definitions/WeaponType.h"
#include <engine/common/Vector2D.h>
#include <engine/ecs/Entity.h>
#include <engine/ecs/World.h>
#include <map>
#include <vector>
#include <game/components/SpriteComponent.h>

namespace game {
namespace equipment {
    class EquipmentFactory {
    public:
        explicit EquipmentFactory(engine::ecs::World& world);
        engine::ecs::Entity& createRandomEquipment(common::Vector2D<double> position) const;

    private:
        engine::ecs::World& m_world;

        std::vector<std::function<void(engine::ecs::Entity&, engine::ecs::World&, std::map<std::string, components::SpriteComponent>)>> m_factories;
        std::map<definitions::ItemType, std::function<void(engine::ecs::Entity&, engine::ecs::World&, std::map<std::string, components::SpriteComponent>)>> m_itemFactoryMap;
        std::map<definitions::WeaponType, std::function<void(engine::ecs::Entity&, engine::ecs::World&, std::map<std::string, components::SpriteComponent>)>> m_weaponFactoryMap;

        std::map<std::string, components::SpriteComponent> m_spriteComponentMap;
    };
}
}