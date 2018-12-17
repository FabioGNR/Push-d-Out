#include "InventorySystem.h"
#include "game/components/DestructibleComponent.h"
#include "game/components/EquipableComponent.h"
#include "game/components/ItemComponent.h"
#include "game/components/PlayerInputComponent.h"
#include "game/components/PositionComponent.h"
#include "game/definitions/Action.h"
#include <engine/input/States.h>

namespace game {
namespace systems {
    using namespace components;

    InventorySystem::InventorySystem(engine::ecs::World& world, engine::input::InputManager* inputManager)
        : m_world{ world }
        , m_inputMaps{ inputManager->getMap() }
    {
    }

    void InventorySystem::update(std::chrono::nanoseconds /* timeStep */)
    {
        m_world.forEachEntityWith<PlayerInputComponent, InventoryComponent, PositionComponent>([&](engine::ecs::Entity& entity) {
            auto& inputComponent = m_world.getComponent<PlayerInputComponent>(entity);
            auto& inventoryComponent = m_world.getComponent<InventoryComponent>(entity);
            auto& analogMap = m_inputMaps->getMap(inputComponent.controllerId);
            const auto pickupAction = definitions::Action::PickupEquippable;
            const auto pickupControl = inputComponent.getKey(pickupAction);

            if (analogMap.hasState(pickupControl, engine::input::States::PRESSED)) {
                attemptPickup(entity, inventoryComponent);
            }
            const auto switchAction = definitions::Action::SwitchWeapon;
            const auto switchControl = inputComponent.getKey(switchAction);
            if (analogMap.hasState(switchControl, engine::input::States::PRESSED)) {
                attemptSwitch(entity, inventoryComponent);
            }
        });
    }

    void InventorySystem::attemptPickup(engine::ecs::Entity& player, InventoryComponent& inventoryComponent)
    {
        double equipableCandidateDistance = -1;
        engine::ecs::Entity* equipableCandidate = nullptr;
        // find the closest entity near the player that can be equipped
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
            // prevent the equipment from being picked up again
            m_world.removeComponent<PositionComponent>(*equipableCandidate);
            m_world.removeComponent<EquipableComponent>(*equipableCandidate);
            // place the equipment in the inventory
            placeInInventory(player, inventoryComponent, equipableCandidate);
        }
    }

    void InventorySystem::render(engine::IRenderer& /*renderer*/)
    {
        // no rendering
    }

    void InventorySystem::attemptSwitch(engine::ecs::Entity& player, components::InventoryComponent& inventoryComponent)
    {
        if (inventoryComponent.otherEquipment.hasValue()) {
            auto& otherEquipment = *inventoryComponent.otherEquipment.get();
            if (inventoryComponent.activeEquipment.hasValue()) {
                auto& activeEquipment = *inventoryComponent.activeEquipment.get();
                inventoryComponent.otherEquipment.set(&activeEquipment);
            }
            inventoryComponent.activeEquipment.set(&otherEquipment);
            // TODO remove position component from active and add to other;
            auto pos = m_world.getComponent<PositionComponent>(player);
            m_world.removeComponent<PositionComponent>(*inventoryComponent.otherEquipment.get());
            m_world.addComponent<PositionComponent>(*inventoryComponent.activeEquipment.get(), pos);
        }
    }

    void InventorySystem::placeInInventory(engine::ecs::Entity& player, components::InventoryComponent& inventoryComponent,
        engine::ecs::Entity* equipment) const
    {
        bool isItem = equipment->hasComponent<ItemComponent>();
        if (isItem) {
            if (inventoryComponent.item.hasValue()) {
                components::DestructibleComponent destructibleComponent{};
                m_world.addComponent<components::DestructibleComponent>(*inventoryComponent.item.get(), destructibleComponent);
                inventoryComponent.item.clear();
            }
            inventoryComponent.item.set(equipment);
        } else {
            bool otherHasEquipment = inventoryComponent.otherEquipment.hasValue();
            bool activeHasEquipment = inventoryComponent.activeEquipment.hasValue();
            // if we already have an active weapon first make sure the slot is clear
            if (activeHasEquipment) {
                if (!otherHasEquipment) {
                    // Other slot is free. Move the currently active equipment to other slot.
                    // This frees up the active equipment slot
                    auto& activeEquipment = *inventoryComponent.activeEquipment.get();
                    inventoryComponent.otherEquipment.set(&activeEquipment);
                } else {
                    // no free slots, destroy the active equipment
                    // so there is room for the new equipment
                    components::DestructibleComponent destructibleComponent{};
                    m_world.addComponent<components::DestructibleComponent>(*inventoryComponent.activeEquipment.get(), destructibleComponent);
                    inventoryComponent.activeEquipment.clear();
                }
            }
            // add equipment to inventory
            inventoryComponent.activeEquipment.set(equipment);

            auto pos = m_world.getComponent<PositionComponent>(player);
            m_world.addComponent<PositionComponent>(*inventoryComponent.activeEquipment.get(), pos);
        }
    }
}
}
