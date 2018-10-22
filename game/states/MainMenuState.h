#pragma once

#include <chrono>
#include <engine/ui/UISystem.h>
#include <game/State.h>
#include <input/KeyMap.h>
#include <events/models/Subscription.h>

namespace game {
class MainMenuState : public engine::State {
private:
    std::unique_ptr<engine::ui::UISystem> m_system;
    std::shared_ptr<engine::events::Subscription<engine::input::KeyMap>> m_subscription;

public:
    explicit MainMenuState(engine::IGame& game);

    void init() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
};
}
