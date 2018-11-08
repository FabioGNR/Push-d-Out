#pragma once

#include <engine/events/models/Subscription.h>
#include <engine/game/State.h>
#include <engine/input/KeyMap.h>
#include <engine/ui/UISystem.h>

#include <chrono>

namespace game {
class MainMenuState : public engine::State {
private:
    std::unique_ptr<engine::ui::UISystem> m_uiSystem;

public:
    explicit MainMenuState(engine::IGame& context);

    void init() override;
    void resume() override;
    void pause() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;

    void close() override;
};
}
