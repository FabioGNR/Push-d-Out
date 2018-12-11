#pragma once
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <functional>
#include <game/components/ActiveCheatsComponent.h>
#include <game/definitions/Action.h>
#include <game/definitions/Cheat.h>
#include <map>

namespace game::systems {
class CheatsSystem : public engine::ecs::BaseSystem<CheatsSystem> {
    // cheat lambda should return true when it should be deleted
    using CheatCommandFunc = std::function<bool(engine::ecs::World*, engine::ecs::Entity&)>;
    engine::ecs::World* m_ecsWorld;
    engine::input::maps::InputMaps* m_inputMaps;
    std::map<definitions::Cheat, CheatCommandFunc> m_cheatCommands;
    std::map<definitions::Action, definitions::Cheat> m_cheatBindings;

    void toggleCheatForPlayer(engine::ecs::Entity& player, definitions::Cheat cheat);
    void updatePlayerActiveCheats();
    void executeActiveCheats();

public:
    CheatsSystem(engine::ecs::World* ecsWorld, engine::input::InputManager* inputManager);

    void update(std::chrono::nanoseconds timeStep) override;

    void render(engine::IRenderer& renderer) override;
};
}