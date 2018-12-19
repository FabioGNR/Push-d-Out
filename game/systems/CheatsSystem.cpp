#include "CheatsSystem.h"
#include <algorithm>
#include <game/components/ActiveCheatsComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/JumpComponent.h>
#include <game/components/LifeComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/WeaponComponent.h>

bool executeInfiniteJump(engine::ecs::World* ecsWorld,
    engine::ecs::Entity& entity)
{
    if (entity.hasComponent<game::components::JumpComponent>()) {
        // auto& jumpComponent = ecsWorld->getComponent<game::components::JumpComponent>(entity);
        // TODO: fix pls
    }
    return false;
}

bool executeNoCooldown(engine::ecs::World* ecsWorld,
    engine::ecs::Entity& entity)
{
    if (!entity.hasComponent<game::components::InventoryComponent>()) {
        return false;
    }
    const auto& inventory = ecsWorld->getComponent<game::components::InventoryComponent>(entity);
    if (!inventory.activeEquipment.hasValue()) {
        return false;
    }
    auto* activeEquipment = inventory.activeEquipment.get();
    if (!activeEquipment->hasComponent<game::components::WeaponComponent>()) {
        return false;
    }
    auto& weaponComponent = ecsWorld->getComponent<game::components::WeaponComponent>(*activeEquipment);
    weaponComponent.wasPrimaryFired = false;
    weaponComponent.wasSecondaryFired = false;
    return false;
}

bool executeResetLives(engine::ecs::World* ecsWorld,
    engine::ecs::Entity& entity)
{
    if (!entity.hasComponent<game::components::LifeComponent>()) {
        return false;
    }
    auto& lifeComponent = ecsWorld->getComponent<game::components::LifeComponent>(entity);
    lifeComponent.count = lifeComponent.maximum;
    return true;
}

namespace game::systems {
using namespace components;

CheatsSystem::CheatsSystem(engine::ecs::World* ecsWorld, engine::input::InputManager* inputManager)
    : m_ecsWorld{ ecsWorld }
    , m_inputMaps{ inputManager->getMap() }
{
    m_cheatBindings[definitions::Action::InfiniteJumpCheat] = definitions::Cheat::InfiniteJump;
    m_cheatBindings[definitions::Action::NoCooldownCheat] = definitions::Cheat::NoCooldown;
    m_cheatBindings[definitions::Action::ResetLivesCheat] = definitions::Cheat::ResetLives;
    m_cheatCommands[definitions::Cheat::InfiniteJump] = executeInfiniteJump;
    m_cheatCommands[definitions::Cheat::NoCooldown] = executeNoCooldown;
    m_cheatCommands[definitions::Cheat::ResetLives] = executeResetLives;
}

void CheatsSystem::update(std::chrono::nanoseconds /*timeStep*/)
{
    updatePlayerActiveCheats();
    executeActiveCheats();
}

void CheatsSystem::render(engine::IRenderer& /*renderer*/)
{
    // do nothing
}

void CheatsSystem::updatePlayerActiveCheats()
{
    m_ecsWorld->forEachEntityWith<PlayerInputComponent>([&](auto& entity) {
        auto& inputComponent = m_ecsWorld->getComponent<PlayerInputComponent>(entity);
        auto& analogMap = m_inputMaps->getMap(inputComponent.controllerId);
        std::for_each(m_cheatBindings.begin(), m_cheatBindings.end(), [&](const auto bindingPair) {
            const auto action = bindingPair.first;
            const auto control = inputComponent.getKey(action);
            const auto cheat = bindingPair.second;
            if (analogMap.hasState(control, engine::input::States::PRESSED)) {
                toggleCheatForPlayer(entity, cheat);
            }
        });
    });
}

void CheatsSystem::executeActiveCheats()
{
    m_ecsWorld->forEachEntityWith<ActiveCheatsComponent>([&](auto& entity) {
        auto& cheatsComponent = m_ecsWorld->getComponent<ActiveCheatsComponent>(entity);
        for (auto it = cheatsComponent.activeCheats.begin(); it != cheatsComponent.activeCheats.end(); /* blank */) {
            const auto cheat = *it;
            auto commandIterator = m_cheatCommands.find(cheat);
            if (commandIterator == m_cheatCommands.end()) {
                cheatsComponent.activeCheats.erase(it++); // remove if no matching command is found
            }
            // the iterator points to a cheat<->function pair, the command to execute the cheat
            bool shouldBeDeleted = (*commandIterator).second(m_ecsWorld, entity);
            if (shouldBeDeleted) {
                cheatsComponent.activeCheats.erase(it++);
            } else {
                ++it;
            }
        }
    });
}

void CheatsSystem::toggleCheatForPlayer(engine::ecs::Entity& player, definitions::Cheat cheat)
{
    if (!player.hasComponent<ActiveCheatsComponent>()) {
        m_ecsWorld->addComponent<ActiveCheatsComponent>(player);
    }
    auto& cheatsComponent = m_ecsWorld->getComponent<ActiveCheatsComponent>(player);
    if (cheatsComponent.isCheatActive(cheat)) {
        cheatsComponent.activeCheats.erase(cheat);
    } else {
        cheatsComponent.activeCheats.insert(cheat);
    }
}
}
