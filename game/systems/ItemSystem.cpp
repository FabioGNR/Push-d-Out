#include "ItemSystem.h"

#include <game/components/BodyComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/ItemComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/ProjectileComponent.h>

#include <engine/graphics/IRenderer.h>
#include <engine/physics/Body.h>
#include <engine/physics/DynamicBody.h>

#include <chrono>
#include <game/components/items/ReverseGravityComponent.h>

using namespace game::components;

void activateReverseGravity(engine::ecs::Entity& entity,
    engine::physics::World& world,
    engine::ecs::World& ecsWorld)
{
    (void)world;
    auto reverseGravityComponent = items::ReverseGravityComponent(entity);
    ecsWorld.addComponent<items::ReverseGravityComponent>(entity, reverseGravityComponent);
}

namespace game {
namespace systems {

    ItemSystem::ItemSystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld, engine::input::InputManager& inputManager)
        : m_ecsWorld(ecsWorld)
        , m_physicsWorld(physicsWorld)
    {
        activateFunctionMap[definitions::ItemType::ReverseGravity] = activateReverseGravity;
        m_inputSubscription = inputManager.subscribe([&](engine::input::KeyMap keymap, engine::events::Subscription<engine::input::KeyMap>&) {
            m_keyMap = keymap;
        });
    }

    void ItemSystem::update(std::chrono::nanoseconds timeStep)
    {
        (void)timeStep;
        // check if players want to active an item
        m_ecsWorld.forEachEntityWith<PlayerInputComponent, InventoryComponent, PositionComponent>([&](engine::ecs::Entity& entity) {
            auto& inventory = m_ecsWorld.getComponent<InventoryComponent>(entity);
            auto& inputComponent = m_ecsWorld.getComponent<PlayerInputComponent>(entity);
            if (inventory.item.hasValue()) {
                engine::ecs::Entity& itemEntity = inventory.item.get();
                if (itemEntity.hasComponent<components::ItemComponent>()) {
                    auto& item = m_ecsWorld.getComponent<components::ItemComponent>(itemEntity);
                    const auto action = definitions::Action::UseItem;
                    if (inputComponent.controls.find(action) != inputComponent.controls.end()) {
                        auto control = inputComponent.controls[action];
                        if (m_keyMap.hasKeyState(control, engine::input::KeyStates::PRESSED)) {
                            if (activateFunctionMap.find(item.type) != activateFunctionMap.end()) {
                                activateFunctionMap[item.type](itemEntity, m_physicsWorld, m_ecsWorld);
                            }
                            inventory.item.clear();
                        }
                    }
                }
            }
        });
    }

    void ItemSystem::render(engine::IRenderer& /* renderer */) {}
}
}