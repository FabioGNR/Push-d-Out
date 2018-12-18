#include "CharacterBuilder.h"
#include "SpriteBuilder.h"

#include <engine/common/RNG.h>
#include <engine/definitions/SystemPriority.h>
#include <game/builders/CharacterSpawnGenerator.h>
#include <game/components/AnimationsComponent.h>
#include <game/components/BodyComponent.h>
#include <game/components/CharacterSpawnComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/DirectionComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/JumpComponent.h>
#include <game/components/LifeComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PlayerNameComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/PunchComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/components/WeaponComponent.h>
#include <game/config/InputConfiguration.h>
#include <game/definitions/Action.h>
#include <game/definitions/BodyGroupIndex.h>
#include <game/equipment/EquipmentFactory.h>
#include <game/exceptions/MissingCharacterSpawnException.h>
#include <game/exceptions/NoPlayersFoundException.h>
#include <game/states/GameState.h>
#include <game/systems/InventorySystem.h>
#include <game/systems/ItemSystem.h>
#include <game/systems/JumpSystem.h>
#include <game/systems/LifeSystem.h>
#include <game/systems/MVPSystem.h>
#include <game/systems/MovementSystem.h>
#include <game/systems/PlayerAnimationSystem.h>
#include <game/systems/PlayerInputSystem.h>
#include <game/systems/PlayerNameSystem.h>
#include <game/systems/PositionSystem.h>
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
        m_ecsWorld.addSystem<systems::MovementSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld);
        m_ecsWorld.addSystem<systems::PositionSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld);
        m_ecsWorld.addSystem<systems::ItemSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_physicsWorld, m_inputManager);
        m_ecsWorld.addSystem<systems::InventorySystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_inputManager);

        const config::InputConfiguration inputConfiguration{};
        const auto& keyboardControls = inputConfiguration.getKeyboardControls();
        const auto& analogControls = inputConfiguration.getAnalogControls();
        const auto& controllerControls = inputConfiguration.getControllerControls();

        std::vector<std::map<std::string, components::SpriteComponent>> playerAnimations;
        playerAnimations.push_back(builders::SpriteBuilder{ assetsFolder + "PlayerGreen.png", assetsFolder + "datafile.json" }.build());
        playerAnimations.push_back(builders::SpriteBuilder{ assetsFolder + "PlayerBlue.png", assetsFolder + "datafile.json" }.build());
        playerAnimations.push_back(builders::SpriteBuilder{ assetsFolder + "PlayerRed.png", assetsFolder + "datafile.json" }.build());
        playerAnimations.push_back(builders::SpriteBuilder{ assetsFolder + "PlayerYellow.png", assetsFolder + "datafile.json" }.build());

        const auto& connectedControllersVector = m_inputManager->getConnectedControllers();

        std::map<engine::ecs::Entity, std::map<std::string, components::SpriteComponent>> entityAnimations;

        auto buildFunc = [&](const size_t& i) {
            // Make character jumpable
            m_ecsWorld.addComponent<components::JumpComponent>(players[i], common::Vector2D{ 0.0, 0.0 });

            // Create a position vector based on a random index
            int randomValue = common::RNG::generate(1, static_cast<int>(positions.size()));
            common::Vector2D<double> position = positions[randomValue - 1];

            // Create a dynamic body for the Physics World
            components::BodyComponent bodyComponent{
                m_physicsWorld.createDynamicBody(position, dimension, players[i].get().id(), static_cast<int>(definitions::BodyGroupIndex::PLAYER))
            };
            m_ecsWorld.addComponent<components::BodyComponent>(players[i], std::move(bodyComponent));

            // Create the dimension component for player entity
            components::DimensionComponent dimensionComponent{ common::Vector2D<double>(1.4, 2.1) };
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

            // Add the player name
            components::PlayerNameComponent name{ "P" + std::to_string((int)i + 1) };
            m_ecsWorld.addComponent<components::PlayerNameComponent>(players[i], name);

            // Create the animations storage for the player entity
            const components::AnimationsComponent playerSpritesComponent{ playerAnimations[i] };
            m_ecsWorld.addComponent<components::AnimationsComponent>(players[i], playerSpritesComponent);

            components::DirectionComponent directionComponent{};
            m_ecsWorld.addComponent<components::DirectionComponent>(players[i], directionComponent);

            // Add keyboard if i is the same or higher than the amount of connected controller
            const auto& connectedControllers = m_inputManager->getConnectedControllers();
            if (std::find(connectedControllers.begin(), connectedControllers.end(), i) != connectedControllers.end()) {
                components::PlayerInputComponent playerInputComponent{ (int)connectedControllers.at(i), controllerControls, analogControls };
                m_ecsWorld.addComponent<components::PlayerInputComponent>(players[i], playerInputComponent);
            } else {
                components::PlayerInputComponent playerInputComponent{ -1, keyboardControls, analogControls };
                m_ecsWorld.addComponent<components::PlayerInputComponent>(players[i], playerInputComponent);
            }

            // Create the life component for player entity
            components::LifeComponent lifeComponent{ 3 };
            m_ecsWorld.addComponent<components::LifeComponent>(players[i], lifeComponent);

            equipment::EquipmentFactory ef{ m_ecsWorld };

            // Add default force gun to player, and portal gun as secondary
            components::InventoryComponent inventoryComponent{};
            inventoryComponent.activeEquipment.set(&ef.get(definitions::WeaponType::ForceGun));
            inventoryComponent.otherEquipment.set(&ef.get(definitions::WeaponType::PortalGun));

            m_ecsWorld.addComponent<components::InventoryComponent>(players[i], inventoryComponent);
            m_ecsWorld.addComponent<components::PunchComponent>(players[i]);
            m_ecsWorld.addComponent<components::MoveComponent>(players[i], common::Vector2D<double>(0, 0));

            // Remove the position
            positions.erase(positions.begin() + randomValue - 1);
        };

        if (game::Game::DEBUG && m_playerCount != connectedControllersVector.size()) {
            // for the keyboard
            buildFunc(m_playerCount - 1); // -1 because this is a count, so it starts at 1, but the player ids start at 0
        }
        std::for_each(connectedControllersVector.begin(), connectedControllersVector.end(), buildFunc);
        m_ecsWorld.addSystem<systems::PlayerAnimationSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld);
    }
}
}
