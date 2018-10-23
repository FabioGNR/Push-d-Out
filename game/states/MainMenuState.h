#pragma once

#include <chrono>
#include <engine/ui/UISystem.h>
#include <game/State.h>
#include <input/KeyMap.h>
#include <events/models/Subscription.h>

namespace game {
class MainMenuState : public engine::State {
private:
    std::unique_ptr<engine::ui::UISystem> m_uiSystem;

public:
    explicit MainMenuState(engine::IGame& game);

    void init() override;
    void resume() override;
    void pause() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;

    void close() override;
};
}
