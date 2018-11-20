#include "CharacterBuilder.h"

#include <engine/common/RNG.h>
#include <engine/definitions/SystemPriority.h>
#include <game/builders/CharacterSpawnGenerator.h>
#include <game/components/BodyComponent.h>
#include <game/components/CharacterSpawnComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/LifeComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/components/WeaponComponent.h>
#include <game/definitions/Action.h>
#include <game/exceptions/MissingCharacterSpawnException.h>
#include <game/exceptions/NoPlayersFoundException.h>
#include <game/systems/InventorySystem.h>
#include <game/systems/ItemSystem.h>
#include <game/systems/LifeSystem.h>
#include <game/systems/MovementSystem.h>
#include <game/systems/PlayerInputSystem.h>
#include <game/systems/PositionSystem.h>
#include <game/systems/SpriteSystem.h>
#include <game/systems/WeaponSystem.h>

namespace game {
namespace builders {
    void CharacterBuilder::build() const
    {
        // Create the necessary player entities
        std::vector<std::reference_wrapper<engine::ecs::Entity>> players{};
        for (size_t i = 0; i < m_playerCount; ++i) {
            players.emplace_back(m_ecsWorld.createEntity());
        }

        if (players.empty()) {
            throw exceptions::NoPlayersFoundException();
        }

        auto positions = CharacterSpawnGenerator::collect(m_ecsWorld);

        // Check if there are enough spawn points for the characters
        if (positions.empty() || m_playerCount > positions.size()) {
            throw exceptions::MissingCharacterSpawnException();
        }

        // Set the dimension of all the players
        common::Vector2D<double> dimension{ 1, 2 };

        // Create the player input scheme for the player entity
        // TODO : Build the key mapper for player controls
        std::map<game::definitions::Action, engine::input::Keys> controls;

        // TODO: Move these actions to some kind of configurations
        controls[definitions::Action::UseWeapon] = engine::input::Keys::F;
        controls[definitions::Action::SwitchWeapon] = engine::input::Keys::X;
        controls[definitions::Action::UseItem] = engine::input::Keys::G;
        controls[definitions::Action::PickupEquippable] = engine::input::Keys::E;
        controls[definitions::Action::MoveLeft] = engine::input::Keys::A;
        controls[definitions::Action::MoveRight] = engine::input::Keys::D;
        controls[definitions::Action::Jump] = engine::input::Keys::SPACE;

        for (size_t i = 0; i < m_playerCount; ++i) {
            // Create a position vector based on a random index
            int randomValue = common::RNG::generate(1, static_cast<int>(positions.size()));
            common::Vector2D<double> position = positions[randomValue - 1];

            // Create a dynamic body for the Physics World
            components::BodyComponent bodyComponent{ m_physicsWorld.createDynamicBody(position, dimension) };
            m_ecsWorld.addComponent<components::BodyComponent>(players[i], bodyComponent);

            // Create the dimension component for player entity
            components::DimensionComponent dimensionComponent{ dimension };
            m_ecsWorld.addComponent<components::DimensionComponent>(players[i], dimensionComponent);

            // Create the position component for player entity
            components::PositionComponent positionComponent{ position };
            m_ecsWorld.addComponent<components::PositionComponent>(players[i], positionComponent);

            components::PlayerInputComponent playerInputComponent{ static_cast<int>(i + 1), controls };
            m_ecsWorld.addComponent<components::PlayerInputComponent>(players[i], playerInputComponent);

            // Create the life component for player entity
            components::LifeComponent lifeComponent{ 3 };
            m_ecsWorld.addComponent<components::LifeComponent>(players[i], lifeComponent);

            // Create the sprite component for the player entity
            components::SpriteComponent spriteComponent{ "sheet", "spriteName" };
            m_ecsWorld.addComponent<game::components::SpriteComponent>(players[i], spriteComponent);

            //Creating force gun entity
            auto& gunEntity = m_ecsWorld.createEntity();
            components::WeaponComponent weaponComponent(1, definitions::WeaponType::ForceGun);
            m_ecsWorld.addComponent<components::WeaponComponent>(gunEntity, weaponComponent);
            components::InventoryComponent inventoryComponent{};
            inventoryComponent.activeEquipment.set(&gunEntity);
            m_ecsWorld.addComponent<components::InventoryComponent>(players[i], inventoryComponent);

            // Remove the position
            positions.erase(positions.begin() + randomValue - 1);
        }
    }
}
}
