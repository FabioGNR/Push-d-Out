#pragma once

#include <chrono>
#include <engine/ui/UISystem.h>
#include <game/State.h>

namespace game {
class MainMenuState : public engine::State {
private:
    std::unique_ptr<engine::ui::UISystem> m_system;
    std::chrono::time_point<std::chrono::steady_clock> m_started;

public:
    explicit MainMenuState(engine::IGame& game);

    void init() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
};
}
