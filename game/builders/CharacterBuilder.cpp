#include "CharacterBuilder.h"
#include "SpriteBuilder.h"

#include <engine/common/RNG.h>
#include <engine/definitions/SystemPriority.h>
#include <game/builders/CharacterSpawnGenerator.h>
#include <game/components/BodyComponent.h>
#include <game/components/CharacterSpawnComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/DirectionComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/JumpComponent.h>
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
#include <game/systems/JumpSystem.h>
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

        // Add the necessary systems into the ECS world before adding components
        m_ecsWorld.addSystem<systems::PlayerInputSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_inputManager);
        m_ecsWorld.addSystem<systems::MovementSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld);
        m_ecsWorld.addSystem<systems::PositionSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld);
        m_ecsWorld.addSystem<systems::SpriteSystem>(engine::definitions::SystemPriority::Medium);
        //m_ecsWorld.addSystem<systems::WeaponSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_physicsWorld, m_inputManager);
        m_ecsWorld.addSystem<systems::ItemSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_physicsWorld, m_inputManager);
        m_ecsWorld.addSystem<systems::InventorySystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_inputManager);

        // Create the player input scheme for the player entity
        // TODO : Build the key mapper for player controls
        std::map<game::definitions::Action, engine::input::Keys> KBM_Controls;
        std::map<game::definitions::Action, engine::input::Keys> controls;
        std::map<game::definitions::Action, engine::input::AnalogKeys> analogControls;

        // TODO: Move these actions to some kind of configurations
        analogControls[definitions::Action::UseWeapon] = engine::input::AnalogKeys::CON_TRIGGER_RIGHT;
        analogControls[definitions::Action::MoveLeft] = engine::input::AnalogKeys::CON_LEFTSTICK_X;
        analogControls[definitions::Action::MoveRight] = engine::input::AnalogKeys::CON_LEFTSTICK_X;
        controls[definitions::Action::Jump] = engine::input::Keys::CON_A;
        controls[definitions::Action::UseItem] = engine::input::Keys::CON_LEFTSTICK;
        controls[definitions::Action::PickupEquippable] = engine::input::Keys::CON_LEFTSHOULDER;
        controls[definitions::Action::SwitchWeapon] = engine::input::Keys::CON_RIGHTSHOULDER;

        KBM_Controls[definitions::Action::UseWeapon] = engine::input::Keys::MOUSE_BUTTON_LEFT;
        KBM_Controls[definitions::Action::SwitchWeapon] = engine::input::Keys::X;
        KBM_Controls[definitions::Action::PickupEquippable] = engine::input::Keys::E;
        KBM_Controls[definitions::Action::MoveLeft] = engine::input::Keys::A;
        KBM_Controls[definitions::Action::MoveRight] = engine::input::Keys::D;
        KBM_Controls[definitions::Action::Jump] = engine::input::Keys::SPACE;
        KBM_Controls[definitions::Action::UseItem] = engine::input::Keys::G;

        std::vector<std::map<std::string, components::SpriteComponent>> playerAnimations;
        playerAnimations.push_back(builders::SpriteBuilder{ assetsFolder + "PlayerGreen.png", assetsFolder + "datafile.json" }.build());
        playerAnimations.push_back(builders::SpriteBuilder{ assetsFolder + "PlayerBlue.png", assetsFolder + "datafile.json" }.build());
        playerAnimations.push_back(builders::SpriteBuilder{ assetsFolder + "PlayerRed.png", assetsFolder + "datafile.json" }.build());
        playerAnimations.push_back(builders::SpriteBuilder{ assetsFolder + "PlayerYellow.png", assetsFolder + "datafile.json" }.build());

        for (size_t i = 0; i < m_playerCount; ++i) {
            // Make character jumpable
            m_ecsWorld.addComponent<components::JumpComponent>(players[i], common::Vector2D{ 0.0, 0.0 });

            // Create a position vector based on a random index
            int randomValue = common::RNG::generate(1, static_cast<int>(positions.size()));
            common::Vector2D<double> position = positions[randomValue - 1];

            // Create a dynamic body for the Physics World
            components::BodyComponent bodyComponent{ m_physicsWorld.createDynamicBody(position, dimension, players[i].get().id()) };
            m_ecsWorld.addComponent<components::BodyComponent>(players[i], bodyComponent);

            // Create the dimension component for player entity
            components::DimensionComponent dimensionComponent{ dimension };
            m_ecsWorld.addComponent<components::DimensionComponent>(players[i], dimensionComponent);

            // Create the position component for player entity
            components::PositionComponent positionComponent{ position };
            m_ecsWorld.addComponent<components::PositionComponent>(players[i], positionComponent);

            // Create the sprite component for the player entity
            auto spriteComponentPair = playerAnimations[i].find("Idle");
            if (spriteComponentPair != playerAnimations[i].end()) {
                auto spriteComponent = spriteComponentPair->second;
                m_ecsWorld.addComponent<components::SpriteComponent>(players[i], spriteComponent);
            }
            components::DirectionComponent directionComponent{};
            m_ecsWorld.addComponent<components::DirectionComponent>(players[i], directionComponent);

            // Add keyboard if i is the same or higher than the amount of connected controller
            // Since we start this for loop at 0 and not at 1 we also have to check if its the same
            if (i >= m_inputManager.getConnectedControllers().size()) {
                components::PlayerInputComponent playerInputComponent{ -1, KBM_Controls, analogControls };
                m_ecsWorld.addComponent<components::PlayerInputComponent>(players[i], playerInputComponent);
            } else {
                components::PlayerInputComponent playerInputComponent{ m_inputManager.getConnectedControllers().at(i), controls, analogControls };
                m_ecsWorld.addComponent<components::PlayerInputComponent>(players[i], playerInputComponent);
            }

            // Create the life component for player entity
            components::LifeComponent lifeComponent{ 3 };
            m_ecsWorld.addComponent<components::LifeComponent>(players[i], lifeComponent);

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
