#include "CharacterBuilder.h"

#include <engine/common/RNG.h>
#include <engine/definitions/SystemPriority.h>
#include <game/components/BodyComponent.h>
#include <game/components/CharacterSpawnComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/components/WeaponComponent.h>
#include <game/definitions/Action.h>
#include <game/exceptions/MissingCharacterSpawnException.h>
#include <game/exceptions/NoPlayersFoundException.h>
#include <game/systems/InventorySystem.h>
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

        // Search for all the CharacterSpawnComponents and push the position in the vector
        std::vector<common::Vector2D<double>> positions{};
        m_ecsWorld.forEachEntityWith<components::CharacterSpawnComponent>([&](engine::ecs::Entity& entity) {
            auto component = m_ecsWorld.getComponent<components::PositionComponent>(entity);
            auto pos = component.position;
            positions.push_back(pos);
        });
        // Check if there are enough spawn points for the characters
        if (positions.empty() || m_playerCount > positions.size()) {
            throw exceptions::MissingCharacterSpawnException();
        }

        // Set the dimension of all the players
        common::Vector2D<double> dimension{ 1, 2 };

        // Add the necessary systems into the ECS world before adding components
        m_ecsWorld.addSystem<systems::PlayerInputSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_inputManager);
        m_ecsWorld.addSystem<systems::MovementSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld);
        m_ecsWorld.addSystem<systems::PositionSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld);
        m_ecsWorld.addSystem<systems::SpriteSystem>(engine::definitions::SystemPriority::Medium);
        m_ecsWorld.addSystem<systems::WeaponSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_physicsWorld, m_inputManager);
        m_ecsWorld.addSystem<systems::InventorySystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_inputManager);
        // Create the player input scheme for the player entity
        // TODO : Build the key mapper for player controls
        std::map<game::definitions::Action, engine::input::Keys> controls;
        std::map<game::definitions::Action , engine::input::AnalogKeys> analogControls;
        // TODO: Move these actions to some kind of configurations
        analogControls[definitions::Action::UseWeapon] = engine::input::AnalogKeys ::CON_TRIGGER_RIGHT;
        //controls[definitions::Action::UseWeapon] = engine::input::Keys ::CON_B;
        controls[definitions::Action::PickupEquippable] = engine::input::Keys::E;
        //controls[definitions::Action::MoveLeft] = engine::input::Keys::Z;
        //controls[definitions::Action::MoveRight] = engine::input::Keys::D;
        analogControls[definitions::Action::MoveLeft] = engine::input::AnalogKeys::CON_LEFTSTICK_X;
        analogControls[definitions::Action::MoveRight] = engine::input::AnalogKeys::CON_LEFTSTICK_X;
        controls[definitions::Action::Jump] = engine::input::Keys::CON_A;

        //components::PlayerInputComponent playerInputComponent{ 1, controls, analogControls };
        //m_ecsWorld.addComponent<components::PlayerInputComponent>(player, playerInputComponent);

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

            components::PlayerInputComponent playerInputComponent{ static_cast<int>(i + 1), controls , analogControls};
            m_ecsWorld.addComponent<components::PlayerInputComponent>(players[i], playerInputComponent);

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
