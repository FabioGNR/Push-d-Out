#include "InventorySystem.h"
#include "game/components/EquipableComponent.h"
#include "game/components/ItemComponent.h"
#include "game/components/PlayerInputComponent.h"
#include "game/components/PositionComponent.h"
#include "game/definitions/Action.h"
#include <engine/input/KeyStates.h>

namespace game {
namespace systems {
    using namespace components;

    InventorySystem::InventorySystem(engine::ecs::World& world, engine::input::InputManager& inputManager)
        : m_world { world }
        , m_inputMap { inputManager.getMap() }
    {
    }

    void InventorySystem::update(std::chrono::nanoseconds /*timeStep*/)
    {
        m_world.forEachEntityWith<PlayerInputComponent, InventoryComponent, PositionComponent>([&](engine::ecs::Entity& entity) {
            auto& inputComponent = m_world.getComponent<PlayerInputComponent>(entity);
            auto& inventoryComponent = m_world.getComponent<InventoryComponent>(entity);

            auto& analogMap = m_inputMap.getMap(inputComponent.controllerId);
            auto action = definitions::Action::PickupEquippable;
            auto control = inputComponent.getKey(action);

            if (analogMap.hasKeyState(control, engine::input::KeyStates::PRESSED)) {
                attemptPickup(entity, inventoryComponent);
            }
        });
    }

    void InventorySystem::attemptPickup(engine::ecs::Entity& player, InventoryComponent& inventoryComponent)
    {
        double equipableCandidateDistance = -1;
        engine::ecs::Entity* equipableCandidate = nullptr;
        m_world.forEachEntityWith<EquipableComponent, PositionComponent>([&](engine::ecs::Entity& entity) {
            const auto& playerPosition = m_world.getComponent<PositionComponent>(player).position;
            const auto& equipablePosition = m_world.getComponent<PositionComponent>(entity).position;
            const auto distance = playerPosition.distance(equipablePosition);
            if (distance < PICKUP_RANGE) {
                if (distance < equipableCandidateDistance || equipableCandidate == nullptr) {
                    equipableCandidateDistance = distance;
                    equipableCandidate = &entity;
                }
            }
        });
        if (equipableCandidate != nullptr) {
            // make sure the spawner knows the item was picked up
            auto& equipableComponent = m_world.getComponent<EquipableComponent>(*equipableCandidate);
            equipableComponent.spawner.hasEquipment = false;
            // prevent the equipment from being picked up again and place it in the inventory
            m_world.removeComponent<PositionComponent>(*equipableCandidate);
            m_world.removeComponent<EquipableComponent>(*equipableCandidate);
            bool isItem = equipableCandidate->hasComponent<ItemComponent>();
            if (isItem) {
                if (inventoryComponent.item.hasValue()) {
                    m_world.destroyEntity(inventoryComponent.item.get());
                    inventoryComponent.item.clear();
                }
                inventoryComponent.item.set(equipableCandidate);
            } else if (inventoryComponent.otherEquipment.hasValue()) {
                if (inventoryComponent.activeEquipment.hasValue()) {
                    m_world.destroyEntity(inventoryComponent.activeEquipment.get());
                    inventoryComponent.activeEquipment.clear();
                }
                inventoryComponent.activeEquipment.set(equipableCandidate);
            } else {
                inventoryComponent.otherEquipment.set(equipableCandidate);
            }
        }
    }

    void InventorySystem::render(engine::IRenderer& /*renderer*/)
    {
        // no rendering
    }
}
}
