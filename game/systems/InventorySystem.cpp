#include "InventorySystem.h"
#include "game/components/EquipableComponent.h"
#include "game/components/PlayerInputComponent.h"
#include "game/components/PositionComponent.h"
#include "game/definitions/Action.h"
#include <engine/input/KeyStates.h>

namespace game {
namespace systems {
    using namespace components;

    InventorySystem::InventorySystem(engine::ecs::World& world, engine::input::InputManager& inputManager)
        : m_world{ world }
    {
        m_inputSubscription = inputManager.subscribe([&](engine::input::KeyMap keymap, engine::events::Subscription<engine::input::KeyMap>&) {
            m_keyMap = keymap;
        });
    }

    void InventorySystem::update(std::chrono::nanoseconds /*timeStep*/)
    {
        m_world.forEachEntityWith<PlayerInputComponent, InventoryComponent, PositionComponent>([&](engine::ecs::Entity& entity) {
            auto& inputComponent = m_world.getComponent<PlayerInputComponent>(entity);
            auto& inventoryComponent = m_world.getComponent<InventoryComponent>(entity);
            const auto action = definitions::Action::PickupEquippable;
            if (inputComponent.controls.find(action) != inputComponent.controls.end()) {
                // determine if control is pressed
                auto control = inputComponent.controls[action];
                if (m_keyMap.hasKeyState(control, engine::input::KeyStates::PRESSED)) {
                    attemptPickup(entity, inventoryComponent);
                }
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
            m_world.removeComponent<EquipableComponent>(*equipableCandidate);
            if (inventoryComponent.otherEquipment.hasValue()) {
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
