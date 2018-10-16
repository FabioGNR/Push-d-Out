#include "CharacterBuilder.h"
#include "game/components/BodyComponent.h"
#include "game/components/DimensionComponent.h"
#include "game/components/PlayerInputComponent.h"
#include "game/components/PositionComponent.h"
#include "game/components/SpriteComponent.h"
#include "game/definitions/Action.h"
#include "game/definitions/Body.h"
#include "game/systems/PlayerInputSystem.h"
#include "game/systems/PositionSystem.h"
#include "game/systems/SpriteSystem.h"
#include <engine/definitions/SystemPriority.h>
#include <game/components/InventoryComponent.h>
#include <game/components/WeaponComponent.h>
#include <game/systems/WeaponSystem.h>

namespace game {
namespace builders {
    void CharacterBuilder::build() const
    {
        // Create entity and define position and dimension
        auto& player = m_ecsWorld.createEntity();

        // TODO: Use the character spawn point position
        common::Vector2D<double> position { 5, 13 };
        common::Vector2D<double> dimension { 1, 2 };

        // Add the necessary systems into the ECS world before adding components
        m_ecsWorld.addSystem<systems::PlayerInputSystem>(engine::definitions::SystemPriority::Medium);
        m_ecsWorld.addSystem<systems::PositionSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld);
        m_ecsWorld.addSystem<systems::SpriteSystem>(engine::definitions::SystemPriority::Medium);
        m_ecsWorld.addSystem<systems::WeaponSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_physicsWorld);

        // Create a dynamic body for the Physics World
        components::BodyComponent bodyComponent { m_physicsWorld.createDynamicBody(position, dimension) };
        m_ecsWorld.addComponent<components::BodyComponent>(player, bodyComponent);

        // Create the dimension component for player entity
        components::DimensionComponent dimensionComponent { dimension };
        m_ecsWorld.addComponent<components::DimensionComponent>(player, dimensionComponent);

        // Create the position component for player entity
        components::PositionComponent positionComponent { position };
        m_ecsWorld.addComponent<components::PositionComponent>(player, positionComponent);

        // Create the player input scheme for the player entity
        // TODO : Build the key mapper for player controls
        std::map<game::definitions::Action, char> controls;
        components::PlayerInputComponent playerInputComponent { 1, controls };
        m_ecsWorld.addComponent<components::PlayerInputComponent>(player, playerInputComponent);

        // Create the sprite component for the player entity
        components::SpriteComponent spriteComponent { "sheet", "spriteName" };
        m_ecsWorld.addComponent<game::components::SpriteComponent>(player, spriteComponent);

        //Creating forcegun entity
        auto& gunEntity = m_ecsWorld.createEntity();
        components::WeaponComponent weaponComponent(1, definitions::WeaponType::ForceGun);
        m_ecsWorld.addComponent<components::WeaponComponent>(gunEntity, weaponComponent);

        components::InventoryComponent inventoryComponent{};
        inventoryComponent.activeEquipment.set(&gunEntity);
        m_ecsWorld.addComponent<components::InventoryComponent>(player, inventoryComponent);
    }
}
}
